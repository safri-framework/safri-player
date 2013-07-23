#ifndef RESTPLAYBACKCONTROLLER_H
#define RESTPLAYBACKCONTROLLER_H

#include "iplaybackcontroller.h"

#include <QStateMachine>
#include <QJsonObject>

class QTimer;
class QNetworkReply;

namespace Core { class Media; }

namespace SafriRESTClient
{
    class RESTClient;

    class RESTPlaybackController : public Core::IPlaybackController
    {
        Q_OBJECT
        Q_INTERFACES(Core::IPlaybackController)
        public:

            explicit RESTPlaybackController(RESTClient* restClient, QObject *parent = 0);

            virtual void setPlaylist(QSharedPointer<Core::IPlaylist>);
            virtual QSharedPointer<Core::IPlaylist> getPlaylist();

            virtual QAction* playAction();
            virtual QAction* pauseAction();
            virtual QAction* stopAction();
            virtual QAction* nextAction();
            virtual QAction* previousAction();
            virtual QAction* playPauseAction();
            virtual QAction* shuffleAction();

            virtual QList<QAction*> getAdditionalActions();

            virtual int getMediaTotalTime();
            virtual int getCurrentTime();
            virtual int getVolume();

        private slots:

            virtual void playStateSlot();
            virtual void pauseStateSlot();
            virtual void stopStateSlot();
            virtual void noDataStateSlot();
            virtual void currentSongFinished();

            // TODO: unnecessarily needed by interface
            // replaced here by noDataStateSlot
            virtual void noDataSlot();

            void nextActionSlot();
            void previousActionSlot();
            void shuffleActionSlot(bool value);

            void playRequestCallback();
            void pauseRequestCallback();
            void stopRequestCallback();
            void nextRequestCallback();
            void previousRequestCallback();

            void statusTimerShot();
            void statusRequestCallback();

        public slots:

            virtual void seek(int playTime);
            virtual void setVolume(int volume);

        private:

            static const int STATUS_TIMER_INTERVAL = 500;

            QAction *m_playPauseAction;
            QAction *m_shuffleAction;
            QAction *m_stopAction;
            QAction *m_nextAction;
            QAction *m_previousAction;
            QAction *m_pauseAction;
            QAction *m_playAction;

            QStateMachine *machine;
            QState* currentState;
            QState *m_play ;
            QState *m_pause ;
            QState *m_stop ;
            QState *m_noData;

            RESTClient* client;
            QTimer* statusTimer;
            int mediaTotalTime;
            int currentTime;
            int volume;

            Core::Media* currentMedia;
            int currentMediaID;
            QString currentCollectionHash;

            void setupActions();

            void setupStateMachine();
            void setupStateTransitions();

            QNetworkReply*  sendRESTRequest(QString request, const char *slot = 0);
            void handleCurrentMediaResonse(QJsonObject jsonCurrentMedia);
            void handleStatusResponse(QJsonObject jsonStatusObject);

    };
}

#endif // RESTPLAYBACKCONTROLLER_H
