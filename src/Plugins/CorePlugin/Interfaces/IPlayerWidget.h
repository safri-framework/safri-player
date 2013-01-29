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

public slots:
        virtual void setVolumeEnabled(bool value) = 0;
        virtual void setSeekerEnabled(bool value) = 0;

};

#endif // IPLAYERWIDGET_H
