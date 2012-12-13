#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>

namespace Ui { class PlayerWidget; }
namespace Core { class IPlaybackController; class Media; }

class PlayerWidget : public QWidget
{
    Q_OBJECT
    public:
        explicit PlayerWidget(QWidget *parent = 0);
        ~PlayerWidget();

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
