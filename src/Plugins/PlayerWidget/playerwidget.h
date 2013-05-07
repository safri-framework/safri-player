#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QtWidgets/QWidget>
#include "Interfaces/IPlayerWidget.h"

namespace Ui { class PlayerWidget; }
namespace Core { class IPlaybackController; class Media; }

class PlayerWidget : public IPlayerWidget
{
    Q_OBJECT
    public:
        explicit PlayerWidget(QWidget *parent = 0);
        ~PlayerWidget();
        virtual PlayerWidgetPosition getPreferedPosition();
    void setVolumeEnabled(bool value);
    void setSeekerEnabled(bool value);


    private slots:

        void on_volumeSlider_sliderMoved(int position);
        void mediaChanged(Core::Media* media);
        void update(int currentTime);

        void on_seekSlider_sliderMoved(int position);

    private:

            Ui::PlayerWidget *ui;
            Core::IPlaybackController* playbackController;
};

#endif // PLAYERWIDGET_H
