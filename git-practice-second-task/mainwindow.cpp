#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
#include <QStyle>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Блок инициализации QTableWidget и QListWidget:
    // Конфигурируем таблицу для хранения параметров создаваемых функций (Текст, Числа, Картинки).
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Тип" << "Амплитуда" << "Частота" << "Толщина" << "Стиль");
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

    // Блок работы с QListView через QStringListModel:
    // Создаем список готовых пресетов математических функций для быстрой загрузки.
    m_presetModel = new QStringListModel(this);
    QStringList presets = {"Стандартный Синус", "Быстрый Косинус", "Тангенсоида"};
    m_presetModel->setStringList(presets);
    ui->listViewPresets->setModel(m_presetModel);

    // Блок загрузки стороннего графического файла:
    // Демонстрируем загрузку готовой картинки "image_2a85de.jpg" из папки сборки в интерфейс.
    QPixmap staticPixmap("image_2a85de.jpg");
    if (!staticPixmap.isNull()) {
        ui->labelImageFile->setPixmap(staticPixmap.scaled(120, 120, Qt::KeepAspectRatio));
    } else {
        ui->labelImageFile->setText("Файл не найден");
    }

    // Блок отрисовки базового пустого поля графика:
    // Сразу генерируем белое полотно, чтобы приложение выглядело аккуратно при старте.
    drawGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Блок обработки нажатия клавиш клавиатуры:
// Нажатие Enter инициирует построение графика, а Delete удаляет выбранную функцию.
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        drawGraph();
    } else if (event->key() == Qt::Key_Delete) {
        on_btnDelete_clicked();
    }
    QMainWindow::keyPressEvent(event);
}

// Блок обработки кликов мыши по форме:
// Считываем координаты клика мыши по окну и выводим информационное окно с позицией курсора.
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QMessageBox::information(this, "Клик мыши", QString("Координаты клика на форме X: %1, Y: %2").arg(event->pos().x()).arg(event->pos().y()));
    }
    QMainWindow::mousePressEvent(event);
}

// Блок контекстного меню:
// Реализует всплывающее меню по правому клику мыши на таблице для быстрого удаления строки.
void MainWindow::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu("Управление", this);
    QAction actionDelete("Удалить функцию", this);
    connect(&actionDelete, &QAction::triggered, this, &MainWindow::on_btnDelete_clicked);
    contextMenu.addAction(&actionDelete);
    contextMenu.exec(ui->tableWidget->viewport()->mapToGlobal(pos));
}

// Блок обработки выбора из QListView:
// Позволяет пользователю мгновенно выставить параметры в поля ввода на основе кликнутого пресета.
void MainWindow::on_listViewPresets_clicked(const QModelIndex &index)
{
    QString presetName = m_presetModel->data(index, Qt::DisplayRole).toString();
    if (presetName == "Стандартный Синус") {
        ui->lineEditAmp->setText("1.0");
        ui->lineEditFreq->setText("1.0");
        ui->comboBoxType->setCurrentIndex(0);
    } else if (presetName == "Быстрый Косинус") {
        ui->lineEditAmp->setText("2.5");
        ui->lineEditFreq->setText("4.0");
        ui->comboBoxType->setCurrentIndex(1);
    } else if (presetName == "Тангенсоида") {
        ui->lineEditAmp->setText("0.5");
        ui->lineEditFreq->setText("0.5");
        ui->comboBoxType->setCurrentIndex(2);
    }
}

// Блок добавления математической функции в массив и интерфейс:
// Считываем текстовые поля, QComboBox, QSlider (толщина) и формируем новый объект.
void MainWindow::on_btnAdd_clicked()
{
    QString type = ui->comboBoxType->currentText();
    double amp = ui->lineEditAmp->text().toDouble();
    double freq = ui->lineEditFreq->text().toDouble();
    int thickness = ui->sliderThickness->value();

    Qt::PenStyle style = Qt::SolidLine;
    if (ui->comboBoxStyle->currentIndex() == 1) style = Qt::DashLine;
    if (ui->comboBoxStyle->currentIndex() == 2) style = Qt::DotLine;

    // Выбираем цвет на основе индекса типа функции
    QColor colors[] = {Qt::red, Qt::blue, Qt::darkGreen};
    QColor chosenColor = colors[ui->comboBoxType->currentIndex() % 3];

    if (amp == 0.0) amp = 1.0;
    if (freq == 0.0) freq = 1.0;

    m_functions.append(TrigFunction(type, amp, freq, chosenColor, thickness, style));

    // Пишем лог в QListWidget (вывод истории действий игрока/пользователя)
    ui->listWidget->addItem(QString("[Добавлено] %1: Амп=%2, Част=%3").arg(type).arg(amp).arg(freq));

    updateUiElements();
}

// Блок удаления выбранной функции:
void MainWindow::on_btnDelete_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0 && currentRow < m_functions.size()) {
        m_functions.removeAt(currentRow);
        ui->listWidget->addItem("[Удалено] Функция из таблицы");
        updateUiElements();
    }
}

// Блок обновления синхронных табличных данных:
// Заполняем QTableWidget текстом, числами через QVariant и иконками файловой системы.
void MainWindow::updateUiElements()
{
    ui->tableWidget->setRowCount(0);
    for (int i = 0; i < m_functions.size(); ++i) {
        ui->tableWidget->insertRow(i);

        QTableWidgetItem *itemType = new QTableWidgetItem(m_functions[i].getType());
        itemType->setIcon(style()->standardIcon(QStyle::SP_FileIcon)); // Картинка/Иконка в таблице

        QTableWidgetItem *itemAmp = new QTableWidgetItem();
        itemAmp->setData(Qt::DisplayRole, m_functions[i].getAmplitude());

        QTableWidgetItem *itemFreq = new QTableWidgetItem();
        itemFreq->setData(Qt::DisplayRole, m_functions[i].getFrequency());

        QTableWidgetItem *itemThick = new QTableWidgetItem();
        itemThick->setData(Qt::DisplayRole, m_functions[i].getThickness());

        QTableWidgetItem *itemStyle = new QTableWidgetItem(ui->comboBoxStyle->itemText(m_functions[i].getStyle() - 1));

        ui->tableWidget->setItem(i, 0, itemType);
        ui->tableWidget->setItem(i, 1, itemAmp);
        ui->tableWidget->setItem(i, 2, itemFreq);
        ui->tableWidget->setItem(i, 3, itemThick);
        ui->tableWidget->setItem(i, 4, itemStyle);
    }
}

// Блок ручного вызова построения тригонометрического графика:
void MainWindow::on_btnPlot_clicked()
{
    drawGraph();
}

// Блок низкоуровневой графической отрисовки (Основная логика математического конструктора):
// Используем QPainter для закраски фигур, текста с настраиваемыми шрифтами и вывода линий в пределах -4pi до 4pi.
void MainWindow::drawGraph()
{
    int w = ui->labelGraph->width();
    int h = ui->labelGraph->height();
    if (w <= 0 || h <= 0) return;

    QPixmap pixmap(w, h);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Графическая фигура (Задний декоративный фон/закраска цветом):
    // Рисуем рамку и закрашиваем её легким градиентным или сплошным цветом.
    painter.setBrush(QBrush(QColor(245, 245, 250)));
    painter.setPen(QPen(Qt::darkGray, 1, Qt::SolidLine));
    painter.drawRect(0, 0, w - 1, h - 1);

    // Настройка масштабирования осей с использованием QScrollBar (Зуммирование):
    double zoomFactor = ui->scrollBarZoom->value() / 50.0;
    if (zoomFactor <= 0.1) zoomFactor = 0.1;

    double minX = -4.0 * M_PI / zoomFactor;
    double maxX = 4.0 * M_PI / zoomFactor;
    double minY = -5.0;
    double maxY = 5.0;

    auto toScreenX = [&](double x) { return ((x - minX) / (maxX - minX)) * w; };
    auto toScreenY = [&](double y) { return h - (((y - minY) / (maxY - minY)) * h); };

    // Отрисовка координатных осей (Толщина и тип линий для графических фигур):
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.drawLine(0, toScreenY(0), w, toScreenY(0));
    painter.drawLine(toScreenX(0), 0, toScreenX(0), h);

    // Вывод текста на графике с кастомным шрифтом и размером:
    QFont axisFont("Courier New", 10, QFont::Bold);
    painter.setFont(axisFont);
    painter.setPen(Qt::darkRed);
    painter.drawText(w - 20, toScreenY(0) - 5, "X");
    painter.drawText(toScreenX(0) + 5, 15, "Y");

    painter.drawText(toScreenX(-4.0 * M_PI), toScreenY(0) + 15, "-4pi");
    painter.drawText(toScreenX(4.0 * M_PI), toScreenY(0) + 15, "4pi");

    // Итеративное построение графиков всех функций из таблицы:
    for (const auto& func : m_functions) {
        painter.setPen(QPen(func.getColor(), func.getThickness(), func.getStyle()));

        bool first = true;
        double prevX = 0, prevY = 0;

        for (int screenX = 0; screenX < w; ++screenX) {
            double x = minX + (double)screenX / w * (maxX - minX);
            double y = func.evaluate(x);

            // Игнорируем точки разрыва (для тангенса)
            if (std::isnan(y) || std::isinf(y) || std::abs(y) > 20.0) {
                first = true;
                continue;
            }

            double screenY = toScreenY(y);

            if (!first) {
                // Избегаем ложного соединения линий на асимптотах тангенса
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