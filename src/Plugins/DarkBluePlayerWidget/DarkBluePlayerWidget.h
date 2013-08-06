#ifndef DARKBLUEPLAYERWIDGET_H
#define DARKBLUEPLAYERWIDGET_H

#include "Interfaces/IPlayerWidget.h"
#include "iplaybackcontroller.h"
#include <QMainWindow>
#include "PlayerControl.h"

namespace Ui {
class DarkBluePlayerWidget;
}

namespace Core {
class Media;
class DataItem;
}

class DarkBluePlayerWidget : public IPlayerWidget
{
    Q_OBJECT
    
    public:

        explicit DarkBluePlayerWidget(QWidget *parent = 0);
        ~DarkBluePlayerWidget();

        virtual PlayerWidgetPosition    getPreferedPosition();
        virtual void                    setVolumeEnabled(bool value);
        virtual void                    setSeekerEnabled(bool value);

    private:

        void                            loadStylesheet();
        QString                         getTimeStringFromMS(int ms);
        QString                         getCoverPath(Core::DataItem* dataItem);
        void                            setNextSongCover(QString coverPath);
        Ui::DarkBluePlayerWidget*   ui;
        QWidget*                    window;
        PlayerControl*              playerControl;
        Core::IPlaybackController*  playbackController;

    private slots:

        void objectAddedToObjectPool(QObject* object);
        void playToggled(bool isPlaying);
        void stateChanged(Core::playState state);
        void update(int currentTime);
        void mediaChanged(Core::Media* media);
        void changePlaybackController();

    protected:

        bool eventFilter(QObject *obj, QEvent *event);

};

#endif // DARKBLUEPLAYERWIDGET_H
