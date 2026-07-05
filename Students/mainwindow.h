#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMenu>
#include "students.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 3) Обработка нажатий клавиш на клавиатуре
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_btnGenerate_clicked();
    void on_btnSortAsc_clicked();
    void on_btnSortDesc_clicked();

    // 5) Обработка нажатия правой клавиши мыши
    void showContextMenu(const QPoint &pos);

private:
    Ui::MainWindow *ui;

    // Вспомогательный метод для добавления студента в UI виджеты
    void addStudentToWidgets(const Student& student);
    void deleteSelectedElement();
};

#endif // MAINWINDOW_H