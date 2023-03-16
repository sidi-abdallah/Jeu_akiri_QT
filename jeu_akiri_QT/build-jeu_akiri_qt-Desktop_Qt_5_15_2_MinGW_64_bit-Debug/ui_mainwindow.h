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
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <include/AkariView.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuitter;
    QAction *actionImprimer;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QComboBox *size_box;
    QLabel *label_2;
    AkariView *Gridwidget;
    QComboBox *level_box;
    QLabel *label;
    QPushButton *changeGridButton;
    QComboBox *timer_box;
    QHBoxLayout *horizontalLayout;
    QPushButton *restartButton;
    QPushButton *doneButton;
    QLabel *timer;
    QLabel *messageLabel;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(918, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/akarigame.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionImprimer = new QAction(MainWindow);
        actionImprimer->setObjectName(QString::fromUtf8("actionImprimer"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        size_box = new QComboBox(centralwidget);
        size_box->addItem(QString());
        size_box->addItem(QString());
        size_box->addItem(QString());
        size_box->setObjectName(QString::fromUtf8("size_box"));

        gridLayout->addWidget(size_box, 0, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        Gridwidget = new AkariView(centralwidget);
        Gridwidget->setObjectName(QString::fromUtf8("Gridwidget"));

        gridLayout->addWidget(Gridwidget, 4, 0, 1, 4);

        level_box = new QComboBox(centralwidget);
        level_box->addItem(QString());
        level_box->addItem(QString());
        level_box->addItem(QString());
        level_box->setObjectName(QString::fromUtf8("level_box"));

        gridLayout->addWidget(level_box, 1, 1, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        changeGridButton = new QPushButton(centralwidget);
        changeGridButton->setObjectName(QString::fromUtf8("changeGridButton"));

        gridLayout->addWidget(changeGridButton, 3, 0, 1, 2);

        timer_box = new QComboBox(centralwidget);
        timer_box->addItem(QString());
        timer_box->addItem(QString());
        timer_box->addItem(QString());
        timer_box->addItem(QString());
        timer_box->addItem(QString());
        timer_box->setObjectName(QString::fromUtf8("timer_box"));

        gridLayout->addWidget(timer_box, 0, 2, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 10);

        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        restartButton = new QPushButton(centralwidget);
        restartButton->setObjectName(QString::fromUtf8("restartButton"));

        horizontalLayout->addWidget(restartButton);

        doneButton = new QPushButton(centralwidget);
        doneButton->setObjectName(QString::fromUtf8("doneButton"));

        horizontalLayout->addWidget(doneButton);

        timer = new QLabel(centralwidget);
        timer->setObjectName(QString::fromUtf8("timer"));

        horizontalLayout->addWidget(timer);

        messageLabel = new QLabel(centralwidget);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        font.setItalic(true);
        messageLabel->setFont(font);

        horizontalLayout->addWidget(messageLabel);

        horizontalLayout->setStretch(3, 8);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 8);
        verticalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 918, 26));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionQuitter->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
#if QT_CONFIG(shortcut)
        actionQuitter->setShortcut(QCoreApplication::translate("MainWindow", "W", nullptr));
#endif // QT_CONFIG(shortcut)
        actionImprimer->setText(QCoreApplication::translate("MainWindow", "Imprimer", nullptr));
        label_3->setText(QString());
        size_box->setItemText(0, QCoreApplication::translate("MainWindow", "7 x 7", nullptr));
        size_box->setItemText(1, QCoreApplication::translate("MainWindow", "10 x 10", nullptr));
        size_box->setItemText(2, QCoreApplication::translate("MainWindow", "14 x 14", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Size :", nullptr));
        level_box->setItemText(0, QCoreApplication::translate("MainWindow", "Easy", nullptr));
        level_box->setItemText(1, QCoreApplication::translate("MainWindow", "Medium", nullptr));
        level_box->setItemText(2, QCoreApplication::translate("MainWindow", "Hard", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "Level : ", nullptr));
        changeGridButton->setText(QCoreApplication::translate("MainWindow", "change grid", nullptr));
        timer_box->setItemText(0, QCoreApplication::translate("MainWindow", "Unlimited", nullptr));
        timer_box->setItemText(1, QCoreApplication::translate("MainWindow", "10 Minutes", nullptr));
        timer_box->setItemText(2, QCoreApplication::translate("MainWindow", "5 Minutes", nullptr));
        timer_box->setItemText(3, QCoreApplication::translate("MainWindow", "3 Minutes", nullptr));
        timer_box->setItemText(4, QCoreApplication::translate("MainWindow", "1 Minutes", nullptr));

        restartButton->setText(QCoreApplication::translate("MainWindow", "Restart", nullptr));
        doneButton->setText(QCoreApplication::translate("MainWindow", "Done", nullptr));
        timer->setText(QCoreApplication::translate("MainWindow", "00:00:00", nullptr));
        messageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
