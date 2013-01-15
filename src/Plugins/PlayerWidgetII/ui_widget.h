/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Tue 15. Jan 21:31:37 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QSlider *seek_slider;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *random;
    QPushButton *previous;
    QPushButton *play;
    QPushButton *next;
    QPushButton *repeat;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(750, 305);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        seek_slider = new QSlider(widget_4);
        seek_slider->setObjectName(QString::fromUtf8("seek_slider"));
        seek_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(seek_slider);


        horizontalLayout->addWidget(widget_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_4 = new QHBoxLayout(widget_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 20, -1);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);


        horizontalLayout->addWidget(widget_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        random = new QPushButton(widget_3);
        random->setObjectName(QString::fromUtf8("random"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/SAFRI_UI/shuffle_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        random->setIcon(icon);

        horizontalLayout_2->addWidget(random);

        previous = new QPushButton(widget_3);
        previous->setObjectName(QString::fromUtf8("previous"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/SAFRI_UI/previous_icon_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        previous->setIcon(icon1);

        horizontalLayout_2->addWidget(previous);

        play = new QPushButton(widget_3);
        play->setObjectName(QString::fromUtf8("play"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/SAFRI_UI/play_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        play->setIcon(icon2);
        play->setIconSize(QSize(17, 19));

        horizontalLayout_2->addWidget(play);

        next = new QPushButton(widget_3);
        next->setObjectName(QString::fromUtf8("next"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/SAFRI_UI/next_icon_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        next->setIcon(icon3);

        horizontalLayout_2->addWidget(next);

        repeat = new QPushButton(widget_3);
        repeat->setObjectName(QString::fromUtf8("repeat"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/SAFRI_UI/repeat_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        repeat->setIcon(icon4);
        repeat->setCheckable(true);

        horizontalLayout_2->addWidget(repeat);


        horizontalLayout->addWidget(widget_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(widget);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        Widget->setProperty("type", QVariant(QApplication::translate("Widget", "mainframe", 0, QApplication::UnicodeUTF8)));
        widget->setProperty("type", QVariant(QApplication::translate("Widget", "inner_mainframe", 0, QApplication::UnicodeUTF8)));
        widget_2->setProperty("type", QVariant(QApplication::translate("Widget", "display", 0, QApplication::UnicodeUTF8)));
        label_2->setText(QString());
        label->setText(QApplication::translate("Widget", "Red hot chili Peppers \n"
"By the way", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "2:47", 0, QApplication::UnicodeUTF8));
        random->setText(QString());
        random->setProperty("type", QVariant(QApplication::translate("Widget", "player_button", 0, QApplication::UnicodeUTF8)));
        random->setProperty("button_size", QVariant(QApplication::translate("Widget", "little", 0, QApplication::UnicodeUTF8)));
        random->setProperty("side", QVariant(QApplication::translate("Widget", "l", 0, QApplication::UnicodeUTF8)));
        previous->setText(QString());
        previous->setProperty("type", QVariant(QApplication::translate("Widget", "player_button", 0, QApplication::UnicodeUTF8)));
        previous->setProperty("button_size", QVariant(QApplication::translate("Widget", "middle", 0, QApplication::UnicodeUTF8)));
        previous->setProperty("side", QVariant(QApplication::translate("Widget", "l", 0, QApplication::UnicodeUTF8)));
        play->setText(QString());
        play->setProperty("type", QVariant(QApplication::translate("Widget", "player_button", 0, QApplication::UnicodeUTF8)));
        play->setProperty("button_size", QVariant(QApplication::translate("Widget", "big", 0, QApplication::UnicodeUTF8)));
        next->setText(QString());
        next->setProperty("type", QVariant(QApplication::translate("Widget", "player_button", 0, QApplication::UnicodeUTF8)));
        next->setProperty("button_size", QVariant(QApplication::translate("Widget", "middle", 0, QApplication::UnicodeUTF8)));
        next->setProperty("side", QVariant(QApplication::translate("Widget", "r", 0, QApplication::UnicodeUTF8)));
        repeat->setText(QString());
        repeat->setProperty("type", QVariant(QApplication::translate("Widget", "player_button", 0, QApplication::UnicodeUTF8)));
        repeat->setProperty("button_size", QVariant(QApplication::translate("Widget", "little", 0, QApplication::UnicodeUTF8)));
        repeat->setProperty("side", QVariant(QApplication::translate("Widget", "r", 0, QApplication::UnicodeUTF8)));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
