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

    // Блок настройки QTableWidget:
    // Устанавливаем количество колонок, заголовки и настраиваем ширину последней колонки.
    // Также задаем выделение целиком всей строки при клике.
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Фамилия" << "Курс" << "Телефон");
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Блок настройки контекстного меню:
    // Разрешаем вызов кастомного контекстного меню (по правому клику мыши) для таблицы
    // и связываем сигнал его вызова со слотом showContextMenu.
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

    // Блок загрузки и отображения картинки:
    // Пытаемся загрузить изображение из рабочей директории программы.
    // Если картинка найдена, масштабируем её с сохранением пропорций, иначе выводим текст.
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

// Блок обработки нажатий клавиш клавиатуры:
// Если пользователь нажимает клавишу Delete, вызывается метод удаления текущего выделенного элемента.
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        deleteSelectedElement();
    }
    QMainWindow::keyPressEvent(event);
}

// Блок создания всплывающего меню:
// Динамически создаем меню, добавляем действие "Удалить" и показываем его
// ровно в тех координатах, где находился курсор мыши при правом клике.
void MainWindow::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Меню"), this);
    QAction actionDelete("Удалить", this);
    connect(&actionDelete, &QAction::triggered, this, &MainWindow::deleteSelectedElement);
    contextMenu.addAction(&actionDelete);
    contextMenu.exec(ui->tableWidget->viewport()->mapToGlobal(pos));
}

// Блок добавления нового студента из интерфейса:
// Считываем данные из полей QLineEdit, QComboBox и QSpinBox.
// Обязательно проверяем, не пустое ли поле фамилии, прежде чем добавить данные.
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

// Блок вывода данных в таблицу (QTableWidget) и список (QListWidget):
// Для таблицы используем QVariant и setData(Qt::DisplayRole, ...),
// чтобы числа сортировались именно как числа (1, 2, 10), а не как строки (1, 10, 2).
// Также к фамилии прикрепляем стандартную иконку папки.
void MainWindow::addStudentToWidgets(const Student& student)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    QTableWidgetItem *itemSurname = new QTableWidgetItem(student.getSurname());
    itemSurname->setIcon(style()->standardIcon(QStyle::SP_DirIcon));

    QTableWidgetItem *itemCourse = new QTableWidgetItem();
    itemCourse->setData(Qt::DisplayRole, static_cast<qlonglong>(student.getCourse()));

    QTableWidgetItem *itemPhone = new QTableWidgetItem();
    itemPhone->setData(Qt::DisplayRole, static_cast<int>(student.getPhone()));

    ui->tableWidget->setItem(row, 0, itemSurname);
    ui->tableWidget->setItem(row, 1, itemCourse);
    ui->tableWidget->setItem(row, 2, itemPhone);

    QString listText = QString("%1 - Курс: %2, Тел: %3")
                           .arg(student.getSurname())
                           .arg(student.getCourse())
                           .arg(student.getPhone());
    ui->listWidget->addItem(listText);
}

// Блок удаления элемента:
// Вызывается по кнопке "Удалить". Использует общий метод удаления.
void MainWindow::on_btnDelete_clicked()
{
    deleteSelectedElement();
}

// Блок логики удаления:
// Определяем выделенную строку в таблице. Если строка выбрана (индекс >= 0),
// удаляем ее из таблицы и синхронно удаляем элемент с таким же индексом из списка QListWidget.
void MainWindow::deleteSelectedElement()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        ui->tableWidget->removeRow(currentRow);
        QListWidgetItem *it = ui->listWidget->takeItem(currentRow);
        delete it;
    }
}

// Блок автоматической генерации массива студентов:
// Считываем запрошенное количество элементов из QSpinBox.
// В цикле создаем студентов со случайными параметрами и добавляем их в виджеты.
void MainWindow::on_btnGenerate_clicked()
{
    int count = ui->spinBoxCount->value();
    for(int i = 0; i < count; ++i) {
        QString surname = "Студент " + QString::number(rand() % 1000);
        qint64 course = (rand() % 5) + 1;
        qint32 phone = (rand() % 900000) + 100000;
        addStudentToWidgets(Student(surname, course, phone));
    }
}

// Блок сортировки списка (QListWidget) по возрастанию:
void MainWindow::on_btnSortAsc_clicked()
{
    ui->listWidget->sortItems(Qt::AscendingOrder);
}

// Блок сортировки списка (QListWidget) по убыванию:
void MainWindow::on_btnSortDesc_clicked()
{
    ui->listWidget->sortItems(Qt::DescendingOrder);
}