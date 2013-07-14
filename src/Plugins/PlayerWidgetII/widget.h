#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
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
    void setSeekerEnabled(bool value);
    void setVolumeEnabled(bool value);




private slots:

    void mediaChanged(Core::Media* media);
    void update(int currentTime);
    void actionChanged();
    void stateChanged(Core::playState state);
    void on_seek_slider_sliderMoved(int position);
    void on_volume_slider_sliderMoved(int position);
    void on_random_toggled(bool checked);

    void on_repeat_toggled(bool checked);
    void volumeChanged(int volume);

private:

    IPlaybackController* m_pbController;
    bool firstPlayback;
    bool newMedia;
    Ui::Widget *ui;
    QMovie* loaderGif;
    void showLoadingIndicator(QString msg);
    void hideLoadingIndicator();

};

#endif // WIDGET_H
