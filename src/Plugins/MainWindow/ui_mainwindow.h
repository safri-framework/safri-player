/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun 3. Feb 22:02:45 2013
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
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPlugins_show;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QWidget *menuBar;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_2;
    QWidget *buttonspace;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QWidget *sidebar_widget_space;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_4;
    QWidget *mainframe;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_frame;
    QVBoxLayout *verticalLayout_4;
    QWidget *player_frame;
    QVBoxLayout *verticalLayout_2;
    QWidget *playlistWidget;
    QHBoxLayout *horizontalLayout_4;
    QWidget *playerWidget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *playerWidget_bottom;
    QVBoxLayout *verticalLayout_7;
    QMenuBar *menubar;
    QMenu *menuPlugin;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1204, 600);
        actionPlugins_show = new QAction(MainWindow);
        actionPlugins_show->setObjectName(QString::fromUtf8("actionPlugins_show"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_6 = new QVBoxLayout(centralwidget);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        menuBar = new QWidget(widget);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setMinimumSize(QSize(60, 0));
        menuBar->setMaximumSize(QSize(32, 16777215));
        verticalLayout_5 = new QVBoxLayout(menuBar);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_2 = new QSpacerItem(42, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

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

        sidebar_widget_space = new QWidget(menuBar);
        sidebar_widget_space->setObjectName(QString::fromUtf8("sidebar_widget_space"));
        verticalLayout_3 = new QVBoxLayout(sidebar_widget_space);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        verticalLayout_5->addWidget(sidebar_widget_space);

        verticalSpacer_4 = new QSpacerItem(42, 28, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_4);


        horizontalLayout_5->addWidget(menuBar);

        mainframe = new QWidget(widget);
        mainframe->setObjectName(QString::fromUtf8("mainframe"));
        horizontalLayout_2 = new QHBoxLayout(mainframe);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget_frame = new QWidget(mainframe);
        widget_frame->setObjectName(QString::fromUtf8("widget_frame"));
        verticalLayout_4 = new QVBoxLayout(widget_frame);
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(10, 10, 0, 10);

        horizontalLayout_2->addWidget(widget_frame);

        player_frame = new QWidget(mainframe);
        player_frame->setObjectName(QString::fromUtf8("player_frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(player_frame->sizePolicy().hasHeightForWidth());
        player_frame->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(player_frame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 10, 10, 10);
        playlistWidget = new QWidget(player_frame);
        playlistWidget->setObjectName(QString::fromUtf8("playlistWidget"));
        sizePolicy.setHeightForWidth(playlistWidget->sizePolicy().hasHeightForWidth());
        playlistWidget->setSizePolicy(sizePolicy);
        horizontalLayout_4 = new QHBoxLayout(playlistWidget);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

        verticalLayout_2->addWidget(playlistWidget);

        playerWidget = new QWidget(player_frame);
        playerWidget->setObjectName(QString::fromUtf8("playerWidget"));
        playerWidget->setMinimumSize(QSize(0, 0));
        horizontalLayout_3 = new QHBoxLayout(playerWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        verticalLayout_2->addWidget(playerWidget);

        verticalLayout_2->setStretch(0, 80);

        horizontalLayout_2->addWidget(player_frame);


        horizontalLayout_5->addWidget(mainframe);


        verticalLayout_6->addWidget(widget);

        playerWidget_bottom = new QWidget(centralwidget);
        playerWidget_bottom->setObjectName(QString::fromUtf8("playerWidget_bottom"));
        verticalLayout_7 = new QVBoxLayout(playerWidget_bottom);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetMaximumSize);

        verticalLayout_6->addWidget(playerWidget_bottom);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1204, 21));
        menuPlugin = new QMenu(menubar);
        menuPlugin->setObjectName(QString::fromUtf8("menuPlugin"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuPlugin->menuAction());
        menuPlugin->addAction(actionPlugins_show);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionPlugins_show->setText(QApplication::translate("MainWindow", "Plugins anzeigen", 0, QApplication::UnicodeUTF8));
        menuBar->setProperty("place", QVariant(QApplication::translate("MainWindow", "menu_left", 0, QApplication::UnicodeUTF8)));
        menuBar->setProperty("type", QVariant(QApplication::translate("MainWindow", "frame", 0, QApplication::UnicodeUTF8)));
        widget_frame->setProperty("type", QVariant(QApplication::translate("MainWindow", "frame", 0, QApplication::UnicodeUTF8)));
        player_frame->setProperty("type", QVariant(QApplication::translate("MainWindow", "frame", 0, QApplication::UnicodeUTF8)));
        menuPlugin->setTitle(QApplication::translate("MainWindow", "Plugin", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
