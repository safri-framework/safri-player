/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Sun 3. Feb 22:03:47 2013
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
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QSlider *seek_slider;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *time_label;
    QSpacerItem *horizontalSpacer_2;
    QLabel *infoLabel;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *random;
    QPushButton *previous;
    QPushButton *play;
    QPushButton *next;
    QPushButton *repeat;
    QSpacerItem *horizontalSpacer;
    QSlider *volume_slider;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1123, 305);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(30);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(30, -1, 30, -1);
        widget_4 = new QWidget(widget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        seek_slider = new QSlider(widget_4);
        seek_slider->setObjectName(QString::fromUtf8("seek_slider"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(seek_slider->sizePolicy().hasHeightForWidth());
        seek_slider->setSizePolicy(sizePolicy);
        seek_slider->setMaximum(1000);
        seek_slider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(seek_slider);


        horizontalLayout->addWidget(widget_4);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy1);
        widget_2->setMinimumSize(QSize(400, 0));
        widget_2->setMaximumSize(QSize(400, 16777215));
        horizontalLayout_4 = new QHBoxLayout(widget_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 20, -1);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        time_label = new QLabel(widget_2);
        time_label->setObjectName(QString::fromUtf8("time_label"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(time_label->sizePolicy().hasHeightForWidth());
        time_label->setSizePolicy(sizePolicy2);
        time_label->setMinimumSize(QSize(100, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("Advent"));
        font.setPointSize(28);
        font.setBold(false);
        font.setWeight(50);
        font.setKerning(false);
        font.setStyleStrategy(QFont::PreferAntialias);
        time_label->setFont(font);

        horizontalLayout_4->addWidget(time_label);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        infoLabel = new QLabel(widget_2);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        infoLabel->setMinimumSize(QSize(250, 0));
        infoLabel->setMaximumSize(QSize(250, 16777215));
        QFont font1;
        font1.setPointSize(14);
        infoLabel->setFont(font1);
        infoLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(infoLabel);


        horizontalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        random = new QPushButton(widget_3);
        random->setObjectName(QString::fromUtf8("random"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/SAFRI_UI/shuffle_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        random->setIcon(icon);
        random->setCheckable(true);

        horizontalLayout_2->addWidget(random);

        previous = new QPushButton(widget_3);
        previous->setObjectName(QString::fromUtf8("previous"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/SAFRI_UI/previous_icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        previous->setIcon(icon1);
        previous->setIconSize(QSize(17, 14));

        horizontalLayout_2->addWidget(previous);

        play = new QPushButton(widget_3);
        play->setObjectName(QString::fromUtf8("play"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/SAFRI_UI/play_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/icons/SAFRI_UI/play_icon.png"), QSize(), QIcon::Normal, QIcon::On);
        play->setIcon(icon2);
        play->setIconSize(QSize(19, 19));
        play->setCheckable(false);

        horizontalLayout_2->addWidget(play);

        next = new QPushButton(widget_3);
        next->setObjectName(QString::fromUtf8("next"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/SAFRI_UI/next_icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        next->setIcon(icon3);
        next->setIconSize(QSize(17, 14));

        horizontalLayout_2->addWidget(next);

        repeat = new QPushButton(widget_3);
        repeat->setObjectName(QString::fromUtf8("repeat"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/SAFRI_UI/repeat_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        repeat->setIcon(icon4);
        repeat->setCheckable(true);

        horizontalLayout_2->addWidget(repeat);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        volume_slider = new QSlider(widget_3);
        volume_slider->setObjectName(QString::fromUtf8("volume_slider"));
        volume_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(volume_slider);


        horizontalLayout->addWidget(widget_3);


        verticalLayout->addWidget(widget);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        Widget->setProperty("type", QVariant(QApplication::translate("Widget", "mainframe", 0, QApplication::UnicodeUTF8)));
        widget->setProperty("type", QVariant(QApplication::translate("Widget", "inner_mainframe", 0, QApplication::UnicodeUTF8)));
        seek_slider->setProperty("type", QVariant(QApplication::translate("Widget", "seeker", 0, QApplication::UnicodeUTF8)));
        widget_2->setProperty("type", QVariant(QApplication::translate("Widget", "display", 0, QApplication::UnicodeUTF8)));
        label_2->setText(QString());
        time_label->setText(QApplication::translate("Widget", "Safri III", 0, QApplication::UnicodeUTF8));
        time_label->setProperty("type", QVariant(QApplication::translate("Widget", "display_label", 0, QApplication::UnicodeUTF8)));
        infoLabel->setText(QString());
        infoLabel->setProperty("type", QVariant(QApplication::translate("Widget", "info_label", 0, QApplication::UnicodeUTF8)));
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
