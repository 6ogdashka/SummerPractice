/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *leftLayout;
    QLabel *labelImage;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEditSurname;
    QLabel *label_2;
    QComboBox *comboBoxCourse;
    QLabel *label_3;
    QSpinBox *spinBoxPhone;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpinBox *spinBoxCount;
    QPushButton *btnGenerate;
    QSpacerItem *verticalSpacer;
    QPushButton *btnSortAsc;
    QPushButton *btnSortDesc;
    QVBoxLayout *rightLayout;
    QTableWidget *tableWidget;
    QListWidget *listWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        leftLayout = new QVBoxLayout();
        leftLayout->setObjectName("leftLayout");
        labelImage = new QLabel(centralwidget);
        labelImage->setObjectName("labelImage");
        labelImage->setMinimumSize(QSize(200, 150));
        labelImage->setFrameShape(QFrame::Box);
        labelImage->setAlignment(Qt::AlignCenter);

        leftLayout->addWidget(labelImage);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        lineEditSurname = new QLineEdit(centralwidget);
        lineEditSurname->setObjectName("lineEditSurname");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditSurname);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        comboBoxCourse = new QComboBox(centralwidget);
        comboBoxCourse->addItem(QString());
        comboBoxCourse->addItem(QString());
        comboBoxCourse->addItem(QString());
        comboBoxCourse->addItem(QString());
        comboBoxCourse->addItem(QString());
        comboBoxCourse->setObjectName("comboBoxCourse");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, comboBoxCourse);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        spinBoxPhone = new QSpinBox(centralwidget);
        spinBoxPhone->setObjectName("spinBoxPhone");
        spinBoxPhone->setMaximum(2147483647);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, spinBoxPhone);


        leftLayout->addLayout(formLayout);

        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName("btnAdd");

        leftLayout->addWidget(btnAdd);

        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName("btnDelete");

        leftLayout->addWidget(btnDelete);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        spinBoxCount = new QSpinBox(centralwidget);
        spinBoxCount->setObjectName("spinBoxCount");
        spinBoxCount->setMinimum(1);
        spinBoxCount->setValue(5);

        horizontalLayout_3->addWidget(spinBoxCount);


        leftLayout->addLayout(horizontalLayout_3);

        btnGenerate = new QPushButton(centralwidget);
        btnGenerate->setObjectName("btnGenerate");

        leftLayout->addWidget(btnGenerate);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftLayout->addItem(verticalSpacer);

        btnSortAsc = new QPushButton(centralwidget);
        btnSortAsc->setObjectName("btnSortAsc");

        leftLayout->addWidget(btnSortAsc);

        btnSortDesc = new QPushButton(centralwidget);
        btnSortDesc->setObjectName("btnSortDesc");

        leftLayout->addWidget(btnSortDesc);


        horizontalLayout->addLayout(leftLayout);

        rightLayout = new QVBoxLayout();
        rightLayout->setObjectName("rightLayout");
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setSortingEnabled(true);

        rightLayout->addWidget(tableWidget);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");

        rightLayout->addWidget(listWidget);


        horizontalLayout->addLayout(rightLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\241\321\202\321\203\320\264\320\265\320\275\321\207\320\265\321\201\320\272\320\260\321\217 \320\221\320\260\320\267\320\260 (\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \342\204\2261)", nullptr));
        labelImage->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\321\201\321\202\320\276 \320\264\320\273\321\217 \320\272\320\260\321\200\321\202\320\270\320\275\320\272\320\270", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\232\321\203\321\200\321\201:", nullptr));
        comboBoxCourse->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        comboBoxCourse->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        comboBoxCourse->setItemText(2, QCoreApplication::translate("MainWindow", "3", nullptr));
        comboBoxCourse->setItemText(3, QCoreApplication::translate("MainWindow", "4", nullptr));
        comboBoxCourse->setItemText(4, QCoreApplication::translate("MainWindow", "5", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275:", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\260", nullptr));
        btnDelete->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\263\320\276", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\264\320\273\321\217 \320\267\320\260\320\263\321\200\321\203\320\267\320\272\320\270:", nullptr));
        btnGenerate->setText(QCoreApplication::translate("MainWindow", "\320\241\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\274\320\260\321\201\321\201\320\270\320\262", nullptr));
        btnSortAsc->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\272\320\260 \321\201\320\277\320\270\321\201\320\272\320\260 (\320\220-\320\257)", nullptr));
        btnSortDesc->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\272\320\260 \321\201\320\277\320\270\321\201\320\272\320\260 (\320\257-\320\220)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
