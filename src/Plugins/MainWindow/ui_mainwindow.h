/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon 10. Dec 17:50:08 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *menuBar;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_2;
    QWidget *buttonspace;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QWidget *mainframe;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_frame;
    QWidget *player_frame;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        menuBar = new QWidget(centralwidget);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setMinimumSize(QSize(60, 0));
        menuBar->setMaximumSize(QSize(32, 16777215));
        verticalLayout_5 = new QVBoxLayout(menuBar);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_2 = new QSpacerItem(42, 28, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_2);

        buttonspace = new QWidget(menuBar);
        buttonspace->setObjectName(QString::fromUtf8("buttonspace"));
        verticalLayout = new QVBoxLayout(buttonspace);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        verticalLayout_5->addWidget(buttonspace);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);


        horizontalLayout->addWidget(menuBar);

        mainframe = new QWidget(centralwidget);
        mainframe->setObjectName(QString::fromUtf8("mainframe"));
        horizontalLayout_2 = new QHBoxLayout(mainframe);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget_frame = new QWidget(mainframe);
        widget_frame->setObjectName(QString::fromUtf8("widget_frame"));

        horizontalLayout_2->addWidget(widget_frame);

        player_frame = new QWidget(mainframe);
        player_frame->setObjectName(QString::fromUtf8("player_frame"));

        horizontalLayout_2->addWidget(player_frame);


        horizontalLayout->addWidget(mainframe);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        menuBar->setProperty("place", QVariant(QApplication::translate("MainWindow", "menu_left", 0, QApplication::UnicodeUTF8)));
        menuBar->setProperty("type", QVariant(QApplication::translate("MainWindow", "frame", 0, QApplication::UnicodeUTF8)));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
