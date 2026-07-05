#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QStyle>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Настройка таблицы
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Фамилия" << "Курс" << "Телефон");
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // 5) Включаем политику контекстного меню для таблицы
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

    // 4) Отображение готовых картинок из файлов (загружаем картинку из задания)
    QPixmap pixmap("image_2a85de.jpg");
    if(!pixmap.isNull()) {
        ui->labelImage->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
    } else {
        ui->labelImage->setText("Картинка\nне найдена");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 3) Обработка нажатия клавиши Delete
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        deleteSelectedElement();
    }
    QMainWindow::keyPressEvent(event);
}

// 5) Вывод всплывающего меню
void MainWindow::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);
    QAction actionDelete("Удалить", this);
    connect(&actionDelete, &QAction::triggered, this, &MainWindow::deleteSelectedElement);
    contextMenu.addAction(&actionDelete);
    contextMenu.exec(ui->tableWidget->viewport()->mapToGlobal(pos));
}

// 8, 9) Добавление элементов
void MainWindow::on_btnAdd_clicked()
{
    QString surname = ui->lineEditSurname->text();
    qint64 course = static_cast<qint64>(ui->comboBoxCourse->currentText().toLongLong());
    qint32 phone = static_cast<qint32>(ui->spinBoxPhone->value());

    if (surname.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите фамилию!");
        return;
    }

    Student student(surname, course, phone);
    addStudentToWidgets(student);
}

void MainWindow::addStudentToWidgets(const Student& student)
{
    // Добавление в QTableWidget
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    // Устанавливаем иконку к текстовому полю (часть пункта 7 - вывод картинок в таблицу)
    QTableWidgetItem *itemSurname = new QTableWidgetItem(student.getSurname());
    itemSurname->setIcon(style()->standardIcon(QStyle::SP_DirIcon));

    QTableWidgetItem *itemCourse = new QTableWidgetItem();
    itemCourse->setData(Qt::DisplayRole, static_cast<qlonglong>(student.getCourse())); // Для правильной числовой сортировки

    QTableWidgetItem *itemPhone = new QTableWidgetItem();
    itemPhone->setData(Qt::DisplayRole, static_cast<int>(student.getPhone()));

    ui->tableWidget->setItem(row, 0, itemSurname);
    ui->tableWidget->setItem(row, 1, itemCourse);
    ui->tableWidget->setItem(row, 2, itemPhone);

    // Добавление в QListWidget
    QString listText = QString("%1 - Курс: %2, Тел: %3")
                           .arg(student.getSurname())
                           .arg(student.getCourse())
                           .arg(student.getPhone());
    ui->listWidget->addItem(listText);
}

// 8, 9) Удаление элементов
void MainWindow::on_btnDelete_clicked()
{
    deleteSelectedElement();
}

void MainWindow::deleteSelectedElement()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        ui->tableWidget->removeRow(currentRow);
        // Синхронно удаляем из ListWidget (предполагая, что индексы совпадают)
        QListWidgetItem *it = ui->listWidget->takeItem(currentRow);
        delete it;
    }
}

// 1) Считать размер массива с текстового поля (генерация)
void MainWindow::on_btnGenerate_clicked()
{
    int count = ui->spinBoxCount->value();
    for(int i = 0; i < count; ++i) {
        QString surname = "Студент " + QString::number(rand() % 1000);
        qint64 course = (rand() % 5) + 1;
        qint32 phone = (rand() % 900000) + 100000; // Генерация случайного номера
        addStudentToWidgets(Student(surname, course, phone));
    }
}

// 11) Сортировка QListWidget
void MainWindow::on_btnSortAsc_clicked()
{
    ui->listWidget->sortItems(Qt::AscendingOrder);
}

void MainWindow::on_btnSortDesc_clicked()
{
    ui->listWidget->sortItems(Qt::DescendingOrder);
}