#ifndef IPLAYERWIDGET_H
#define IPLAYERWIDGET_H

#include <QWidget>
#include "../CorePlugin_global.h"


class COREPLUGINSHARED_EXPORT IPlayerWidget : public QWidget
{
    Q_OBJECT

public:


    enum PlayerWidgetPosition
    {
        BOTTOM,
        UNDER_PLAYLIST,
        TOP
    };


    IPlayerWidget(QWidget* parent);
    virtual PlayerWidgetPosition getPreferedPosition() = 0;
     virtual ~IPlayerWidget();
};

#endif // IPLAYERWIDGET_H
