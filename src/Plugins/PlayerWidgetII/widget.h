#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Interfaces/IPlayerWidget.h"
#include "iplaybackcontroller.h"
#include "CoreData/media.h"
#include "PlayerWidgetII_global.h"

namespace Ui {
class Widget;
}

using namespace Core;
class PLAYERWIDGETIISHARED_EXPORT Widget : public IPlayerWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    virtual PlayerWidgetPosition getPreferedPosition();
    ~Widget();

private slots:
    void mediaChanged(Core::Media* media);
    void update(int currentTime);
    void actionChanged();
    void stateChanged(playState state);
    void on_seek_slider_sliderMoved(int position);

private:
    IPlaybackController* m_pbController;
    Ui::Widget *ui;

};

#endif // WIDGET_H
