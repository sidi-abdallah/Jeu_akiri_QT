/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "include/AkariView.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    AkariView *GridWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *level_box_2;
    QLabel *size_label;
    QPushButton *pushButton;
    QComboBox *size_box;
    QComboBox *level_box;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(99, 119, 211, 221));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        GridWidget = new AkariView(verticalLayoutWidget);
        GridWidget->setObjectName(QString::fromUtf8("GridWidget"));

        verticalLayout->addWidget(GridWidget);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(80, 10, 160, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        level_box_2 = new QLabel(gridLayoutWidget);
        level_box_2->setObjectName(QString::fromUtf8("level_box_2"));

        gridLayout->addWidget(level_box_2, 1, 0, 1, 1);

        size_label = new QLabel(gridLayoutWidget);
        size_label->setObjectName(QString::fromUtf8("size_label"));

        gridLayout->addWidget(size_label, 0, 0, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 2, 0, 1, 2);

        size_box = new QComboBox(gridLayoutWidget);
        size_box->addItem(QString());
        size_box->addItem(QString());
        size_box->addItem(QString());
        size_box->setObjectName(QString::fromUtf8("size_box"));

        gridLayout->addWidget(size_box, 0, 1, 1, 1);

        level_box = new QComboBox(gridLayoutWidget);
        level_box->addItem(QString());
        level_box->addItem(QString());
        level_box->addItem(QString());
        level_box->setObjectName(QString::fromUtf8("level_box"));

        gridLayout->addWidget(level_box, 1, 1, 1, 1);

        gridLayout->setRowMinimumHeight(0, 1);
        gridLayout->setRowMinimumHeight(1, 1);
        gridLayout->setRowMinimumHeight(2, 4);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        level_box_2->setText(QCoreApplication::translate("MainWindow", "Level :", nullptr));
        size_label->setText(QCoreApplication::translate("MainWindow", "Size : ", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        size_box->setItemText(0, QCoreApplication::translate("MainWindow", "7 * 7", nullptr));
        size_box->setItemText(1, QCoreApplication::translate("MainWindow", "10 * 10", nullptr));
        size_box->setItemText(2, QCoreApplication::translate("MainWindow", "14 * 14", nullptr));

        level_box->setItemText(0, QCoreApplication::translate("MainWindow", "Easy", nullptr));
        level_box->setItemText(1, QCoreApplication::translate("MainWindow", "Medium", nullptr));
        level_box->setItemText(2, QCoreApplication::translate("MainWindow", "Hard", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
