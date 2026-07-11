#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QShortcut>      // Подключаем класс для горячих клавиш
#include <QKeySequence>   // Подключаем класс для кодов клавиш
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация таблицы
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"Тип", "Угол", "Цвет", "Стиль"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Инициализация пресетов
    m_presetModel = new QStringListModel(this);
    QStringList presets = {"Синус", "Косинус", "Тангенс"};
    m_presetModel->setStringList(presets);
    ui->listViewPresets->setModel(m_presetModel);

    // Блок загрузки стороннего графического файла
    QPixmap staticPixmap("image_2a85de.jpg");
    if (!staticPixmap.isNull()) {
        ui->labelImageFile->setPixmap(staticPixmap.scaled(120, 120, Qt::KeepAspectRatio));
    } else {
        ui->labelImageFile->setText("Файл не найден");
    }

    // ИСПРАВЛЕНИЕ: Глобальный перехват клавиши Delete через QShortcut
    QShortcut *deleteShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    connect(deleteShortcut, &QShortcut::activated, this, &MainWindow::on_btnDelete_clicked);

    drawGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Выбор математического пресета:
void MainWindow::on_listViewPresets_clicked(const QModelIndex &index)
{
    QString presetName = m_presetModel->data(index, Qt::DisplayRole).toString();
    if (presetName == "Синус") {
        ui->comboBoxType->setCurrentIndex(0);
        ui->comboBoxMultiplier->setCurrentIndex(0);
    } else if (presetName == "Косинус") {
        ui->comboBoxType->setCurrentIndex(1);
        ui->comboBoxMultiplier->setCurrentIndex(0);
    } else if (presetName == "Тангенс") {
        ui->comboBoxType->setCurrentIndex(2);
        ui->comboBoxMultiplier->setCurrentIndex(0);
    }
}

// Считывание всех QComboBox и добавление функции
void MainWindow::on_btnAdd_clicked()
{
    QString type = ui->comboBoxType->currentText();

    int multiplier = ui->comboBoxMultiplier->currentIndex() + 1;

    Qt::PenStyle style = Qt::SolidLine;
    if (ui->comboBoxStyle->currentIndex() == 1) style = Qt::DashLine;
    if (ui->comboBoxStyle->currentIndex() == 2) style = Qt::DotLine;

    QColor color = Qt::red;
    switch(ui->comboBoxColor->currentIndex()) {
    case 0: color = Qt::red; break;
    case 1: color = Qt::blue; break;
    case 2: color = Qt::darkGreen; break;
    case 3: color = Qt::black; break;
    }

    m_functions.append(TrigFunction(type, multiplier, color, style));
    ui->listWidget->addItem(QString("[Добавлено] %1(%2x)").arg(type).arg(multiplier));

    updateUiElements();
}

// Удаление функции из списка
void MainWindow::on_btnDelete_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0 && currentRow < m_functions.size()) {
        m_functions.removeAt(currentRow);
        ui->listWidget->addItem("[Удалено] Функция");
        updateUiElements();
    }
}

// Обновление таблицы интерфейса
void MainWindow::updateUiElements()
{
    ui->tableWidget->setRowCount(0);
    for (int i = 0; i < m_functions.size(); ++i) {
        ui->tableWidget->insertRow(i);

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(m_functions[i].getType()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(m_functions[i].getMultiplier()) + "x"));

        QString colorStr = "Красный";
        if (m_functions[i].getColor() == Qt::blue) colorStr = "Синий";
        else if (m_functions[i].getColor() == Qt::darkGreen) colorStr = "Зеленый";
        else if (m_functions[i].getColor() == Qt::black) colorStr = "Черный";

        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(colorStr));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(ui->comboBoxStyle->itemText(m_functions[i].getStyle() - 1)));
    }
}

// Кнопка принудительного вывода графика
void MainWindow::on_btnPlot_clicked()
{
    drawGraph();
}

// Логика отрисовки на основе QPainter
void MainWindow::drawGraph()
{
    int w = ui->labelGraph->width();
    int h = ui->labelGraph->height();
    if (w <= 0 || h <= 0) return;

    QPixmap pixmap(w, h);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(QBrush(QColor(245, 245, 250)));
    painter.setPen(QPen(Qt::darkGray, 1, Qt::SolidLine));
    painter.drawRect(0, 0, w - 1, h - 1);

    double zoomFactor = ui->scrollBarZoom->value() / 50.0;
    if (zoomFactor <= 0.1) zoomFactor = 0.1;

    double minX = -4.0 * M_PI / zoomFactor;
    double maxX = 4.0 * M_PI / zoomFactor;

    double minY = -2.0;
    double maxY = 2.0;

    auto toScreenX = [&](double x) { return ((x - minX) / (maxX - minX)) * w; };
    auto toScreenY = [&](double y) { return h - (((y - minY) / (maxY - minY)) * h); };

    // Отрисовка координатных осей
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.drawLine(0, toScreenY(0), w, toScreenY(0));
    painter.drawLine(toScreenX(0), 0, toScreenX(0), h);

    QFont axisFont("Courier New", 10, QFont::Bold);
    painter.setFont(axisFont);
    painter.setPen(Qt::darkRed);
    painter.drawText(w - 20, toScreenY(0) - 5, "X");
    painter.drawText(toScreenX(0) + 5, 15, "Y");
    painter.drawText(toScreenX(-4.0 * M_PI), toScreenY(0) + 15, "-4pi");
    painter.drawText(toScreenX(4.0 * M_PI), toScreenY(0) + 15, "4pi");

    // Итеративное построение функций
    for (const auto& func : m_functions) {
        painter.setPen(QPen(func.getColor(), 2, func.getStyle()));

        bool first = true;
        double prevX = 0, prevY = 0;

        for (int screenX = 0; screenX < w; ++screenX) {
            double x = minX + (double)screenX / w * (maxX - minX);
            double y = func.evaluate(x);

            if (std::isnan(y) || std::isinf(y) || std::abs(y) > 20.0) {
                first = true;
                continue;
            }

            double screenY = toScreenY(y);

            if (!first) {
                if (std::abs(screenY - prevY) < h * 0.8) {
                    painter.drawLine(prevX, prevY, screenX, screenY);
                }
            }
            prevX = screenX;
            prevY = screenY;
            first = false;
        }
    }

    ui->labelGraph->setPixmap(pixmap);
}