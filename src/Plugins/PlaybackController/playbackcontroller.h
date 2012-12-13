#ifndef PLAYBACKCONTROLLER_H
#define PLAYBACKCONTROLLER_H
#include <QStateMachine>
#include "Interfaces/IAudioBackend.h"
#include "iplaybackcontroller.h"
#include <QAction>
#include <CoreData/media.h>

//using namespace Core;
class PlaybackController : public Core::IPlaybackController
{
    Q_OBJECT
    Q_INTERFACES(Core::IPlaybackController)
    public:

        PlaybackController();

        void setPlaylist(Core::IPlaylist* playlist);
        Core::IPlaylist* getPlaylist();

        QAction* playAction();
        QAction* playPauseAction();
        QAction* pauseAction();
        QAction* stopAction();
        QAction* nextAction();
        QAction* previousAction();
        QList<QAction*> getAdditionalActions();

        int getMediaTotalTime();
        int getVolume();


protected:

        Core::IPlaylist *playlist;
        void playMedia(Core::Media* media);

public slots:
        void seek(int playTime);
        virtual void setVolume(int volume);

    signals:

        void hasData();

private:

        QStateMachine *machine;
        QState *m_play ;
        QState *m_pause ;
        QState *m_stop ;
        QState *m_noData;

        QAction *m_playPauseAction;
        QAction *m_shuffleAction;
        QAction *m_stopAction;
        QAction *m_nextAction;
        QAction *m_previousAction;
        QAction *m_pauseAction;
        QAction *m_playAction;

        QState* currentState;
        Core::IAudioBackend* audioBackend;
        Core::Media* currentMedia;
        void setupActions();
        void setupTransitions();
        void setupSignalAndSlots();

        bool stopped;

private slots:

        void playStateSlot();
        void pauseStateSlot();
        void stopStateSlot();
        void currentSongFinished();
        void nextActionSlot();
        void previousActionSlot();
        void shuffleActionSlot(bool value);
        void noDataSlot();
        void audioBackendUpdate(int currentTime);



};

#endif // PLAYBACKCONTROLLER_H
