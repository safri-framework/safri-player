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

            virtual ~RESTPlaybackController();

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
            virtual Core::playState getCurrentState();
            virtual int getVolume();

        private slots:

            void playActionSlot();
            void pauseActionSlot();
            void playPauseActionSlot();
            void stopActionSlot();
            void currentSongFinished();

            void nextActionSlot();
            void previousActionSlot();
            void shuffleActionSlot(bool value);

            void playRequestCallback();
            void pauseRequestCallback();
            void stopRequestCallback();
            void nextRequestCallback();
            void previousRequestCallback();

            void requestStatus();
            void statusRequestCallback();

        signals:

            void connectionFailed();

        public slots:

            virtual void seek(int playTime);
            virtual void setVolume(int volume);

        private:

            static const int STATUS_TIMER_INTERVAL = 500;
            static const int STATUS_TIMER_INITIAL_SHOT = 500;
            static const int STATUS_TIMER_PLAY_INTERVAL = 500;
            static const int STATUS_TIMER_STOP_INTERVAL = 2000;
            static const int STATUS_TIMER_PAUSE_INTERVAL = 1000;

            Core::playState currentState;

            QAction *m_playPauseAction;
            QAction *m_shuffleAction;
            QAction *m_stopAction;
            QAction *m_nextAction;
            QAction *m_previousAction;
            QAction *m_pauseAction;
            QAction *m_playAction;

            RESTClient* client;
            QTimer* statusTimer;
            int mediaTotalTime;
            int currentTime;
            int volume;

            Core::Media* currentMedia;
            int currentMediaID;
            QString currentCollectionHash;

            void setupActions();
            void switchState(Core::playState newState);
            void switchState(QString stateName);

            QNetworkReply*  sendRESTRequest(QString request, const char *slot);

            /**
             * @brief convinient function to send a request which will be scheduled for automatic deletion
             * @param request
             */
            void            sendRESTRequest(QString request);

            void handleCurrentMediaResonse(QJsonObject jsonCurrentMedia);
            void handleStatusResponse(QJsonObject jsonStatusObject);

    };
}

#endif // RESTPLAYBACKCONTROLLER_H
