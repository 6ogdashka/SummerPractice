#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QVector>
#include "TrigFunction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_btnPlot_clicked();
    void on_listViewPresets_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QVector<TrigFunction> m_functions;
    QStringListModel *m_presetModel;

    void updateUiElements();
    void drawGraph();
};

#endif