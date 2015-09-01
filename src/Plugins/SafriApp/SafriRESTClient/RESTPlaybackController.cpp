#include "RESTPlaybackController.h"

#include <QtWidgets/QStyle>
#include <QtWidgets/QApplication>
#include <QDebug>

#include <QNetworkReply>
#include <QTimer>
#include <QJsonDocument>
#include "RESTClient.h"

#include "RESTActions.h"
#include "RESTSong.h"

using namespace Core;
using namespace SafriRESTClient;

RESTPlaybackController::RESTPlaybackController(RESTClient *restClient, QObject *parent) :
    currentState(Core::NODATA), statusTimer(new QTimer(this)), client(restClient),  currentTime(0), mediaTotalTime(-1)
{
    this->setParent(parent);

    setupActions();

    connect(statusTimer, SIGNAL(timeout()), this, SLOT(requestStatus()));

    /*
     * If we request the initial state here, the mediaChanged signal will
     * be emitted too early, so the view will miss this initial important
     * event. Therefore we're delaying the initial state request a little bit.
     */

    // requestStatus();

    statusTimer->singleShot(STATUS_TIMER_INITIAL_SHOT, this, SLOT(requestStatus()));
}

RESTPlaybackController::~RESTPlaybackController()
{
    qDebug() << "~RESTPlaybackController: stopping statusTimer";
    statusTimer->stop();
}

// ****************** BEGIN INTERFACE IMPLEMENTATION ******************

void RESTPlaybackController::setPlaylist(QSharedPointer<IPlaylist>)
{
    // unused
}

QSharedPointer<IPlaylist> RESTPlaybackController::getPlaylist()
{
    // unused
    return QSharedPointer<IPlaylist>();
}


QAction* RESTPlaybackController::playAction()
{
   return m_playAction;
}

QAction* RESTPlaybackController::pauseAction()
{
   return m_pauseAction;
}

QAction* RESTPlaybackController::stopAction()
{
    return m_stopAction;
}

QAction* RESTPlaybackController::nextAction()
{
    return m_nextAction;
}

QAction* RESTPlaybackController::previousAction()
{
    return m_previousAction;
}

QAction* RESTPlaybackController::playPauseAction()
{
    return m_playPauseAction;
}

QAction* RESTPlaybackController::shuffleAction()
{
    return m_shuffleAction;
}

QList<QAction *> RESTPlaybackController::getAdditionalActions()
{
    // unused
    return QList<QAction*>();
}


// ***** BEGIN ACTUAL WORK IS DONE HERE *****

    void RESTPlaybackController::currentSongFinished()
    {
    }

    void RESTPlaybackController::seek(int playTime)
    {
        QString seekRequest = RESTAction::PLAYER_SEEK;
        seekRequest.replace(QRegExp("%%SEEKTO%%"), QString::number(playTime));

        sendRESTRequest(seekRequest);
    }

    int RESTPlaybackController::getVolume()
    {
        return volume;
    }

    void RESTPlaybackController::setVolume(int volume)
    {
        QString volumeRequest = RESTAction::PLAYER_VOLUME;
        volumeRequest.replace(QRegExp("%%VOLUME%%"), QString::number(volume));

        sendRESTRequest(volumeRequest);
    }

    int RESTPlaybackController::getMediaTotalTime()
    {
        return mediaTotalTime;
    }

    int RESTPlaybackController::getCurrentTime()
    {
        return currentTime;
    }

    playState RESTPlaybackController::getCurrentState()
    {
        return currentState;
    }

// ***** END ACTUAL WORK IS DONE HERE *****

// ****************** END INTERFACE IMPLEMENTATION ******************

void RESTPlaybackController::setupActions()
{

    m_playAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    connect(m_playAction, SIGNAL(triggered()), this, SLOT(playActionSlot()));

    m_pauseAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
    connect(m_pauseAction, SIGNAL(triggered()), this, SLOT(pauseActionSlot()));

    m_playPauseAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    m_playPauseAction->setShortcut(tr("Ctrl+P"));
    m_playPauseAction->setDisabled(false);
    connect(m_playPauseAction, SIGNAL(triggered()), this, SLOT(playPauseActionSlot()));

    m_stopAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    m_stopAction->setShortcut(tr("Ctrl+S"));
    m_stopAction->setDisabled(false);
    connect(m_stopAction, SIGNAL(triggered()), this, SLOT(stopActionSlot()));

    m_nextAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaSkipForward), tr("Next"), this);
    m_nextAction->setShortcut(tr("Ctrl+N"));
    connect(m_nextAction,SIGNAL(triggered()) ,this, SLOT(nextActionSlot()));

    m_previousAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaSkipBackward), tr("Previous"), this);
    m_previousAction->setShortcut(tr("Ctrl+R"));
    connect(m_previousAction,SIGNAL(triggered()) ,this, SLOT(previousActionSlot()));

    m_shuffleAction = new QAction(QIcon(":icons/ressources/shuffle_icon.png"), tr("Shuffle"), this);
    m_shuffleAction->setCheckable(true);
    m_shuffleAction->setChecked(false);
    connect(m_shuffleAction, SIGNAL(triggered(bool)), this, SLOT(shuffleActionSlot(bool)));
}

void RESTPlaybackController::switchState(playState newState)
{
    if (newState == currentState)
    {
        return;
    }

    switch (newState)
    {
        case Core::STOP:

            m_playAction->setEnabled(true);
            m_playPauseAction->setEnabled(true);
            m_pauseAction->setEnabled(false);
            m_stopAction->setDisabled(true);

            statusTimer->start(STATUS_TIMER_STOP_INTERVAL);

            break;

        case Core::PLAY:

            m_shuffleAction->setDisabled(false);
            m_nextAction->setDisabled(false);
            m_previousAction->setDisabled(false);
            m_playPauseAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPause));
            m_stopAction->setDisabled(false);
            m_playPauseAction->setDisabled(false);
            m_playAction->setDisabled(true);
            m_pauseAction->setDisabled(false);

            statusTimer->start(STATUS_TIMER_PLAY_INTERVAL);

            break;

        case Core::PAUSE:

            m_pauseAction->setDisabled(true);
            m_playAction->setEnabled(true);
            m_playPauseAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
            m_playPauseAction->setEnabled(true);

            statusTimer->start(STATUS_TIMER_PAUSE_INTERVAL);

            break;

        case Core::NODATA:

            statusTimer->start(STATUS_TIMER_STOP_INTERVAL);
            break;

        default:

            break;
    }

    currentState = newState;
    Q_EMIT stateChanged(currentState);
}

void RESTPlaybackController::switchState(QString stateName)
{
    Core::playState state = Core::NODATA;

    if (stateName == "PLAY")
    {
        state = Core::PLAY;
    }
    if (stateName == "PAUSE")
    {
        state = Core::PAUSE;
    }
    if (stateName == "STOP")
    {
        state = Core::STOP;
    }
    if (stateName == "NODATA")
    {
        state = Core::NODATA;
    }

    switchState(state);
}

void RESTPlaybackController::playActionSlot()
{
    //qDebug() << "PLAY";
    sendRESTRequest(RESTAction::PLAYER_PLAY, SLOT(playRequestCallback()));
}

void RESTPlaybackController::pauseActionSlot()
{
    //qDebug() << "PAUSE";
    sendRESTRequest(RESTAction::PLAYER_PAUSE, SLOT(pauseRequestCallback()));
}

void RESTPlaybackController::playPauseActionSlot()
{
    if (currentState == Core::PLAY)
    {
        m_pauseAction->trigger();
    }
    else
    {
        m_playAction->trigger();
    }
}

void RESTPlaybackController::stopActionSlot()
{
    //qDebug() << "STOP";
    sendRESTRequest(RESTAction::PLAYER_STOP, SLOT(stopRequestCallback()));
}

void RESTPlaybackController::nextActionSlot()
{
    //qDebug() << "NEXT";
    sendRESTRequest(RESTAction::PLAYER_NEXT, SLOT(nextRequestCallback()));
}

void RESTPlaybackController::previousActionSlot()
{
    //qDebug() << "PREVIOUS";
    sendRESTRequest(RESTAction::PLAYER_PREVIOUS, SLOT(previousRequestCallback()));
}

void RESTPlaybackController::shuffleActionSlot(bool value)
{
    Q_UNUSED( value )
}

// ****************** BEGIN NETWORK HANDLING ******************

void RESTPlaybackController::playRequestCallback()
{
    //qDebug() << "playRequestCallback";

    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    QByteArray bArray;

    if ( !reply )
    {
        qDebug() << "network reply null";

        return;
    }
    if(reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError)
    {
        bArray = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson( bArray );
        QJsonObject jsonObject = jsonDoc.object();

        handleStatusResponse(jsonObject);

        switchState(Core::PLAY);
    }

    reply->deleteLater();
}

void RESTPlaybackController::pauseRequestCallback()
{
    //qDebug() << "pauseRequestCallback";

    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );

    if ( !reply )
    {
        qDebug() << "network reply null";

        return;
    }

    if(reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError)
    {
        switchState(Core::PAUSE);
    }

    reply->deleteLater();
}

void RESTPlaybackController::stopRequestCallback()
{
    //qDebug() << "stopRequestCallback";

    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );

    if ( !reply )
    {
        qDebug() << "network reply null";

        return;
    }

    if(reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError)
    {
        switchState(Core::STOP);
    }

    reply->deleteLater();
}

void RESTPlaybackController::nextRequestCallback()
{
    //qDebug() << "nextRequestCallback";

    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    QByteArray bArray;

    if ( !reply )
    {
        qDebug() << "network reply null";

        return;
    }
    if(reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError)
    {
        bArray = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson( bArray );
        QJsonObject jsonObject = jsonDoc.object();

        handleStatusResponse(jsonObject);

        switchState(Core::PLAY);
    }

    reply->deleteLater();
}

void RESTPlaybackController::previousRequestCallback()
{
    //qDebug() << "previousRequestCallback";
    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    QByteArray bArray;

    if ( !reply )
    {
        qDebug() << "network reply null";

        return;
    }
    if(reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError)
    {
        bArray = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson( bArray );
        QJsonObject jsonObject = jsonDoc.object();

        handleStatusResponse(jsonObject);

        switchState(Core::PLAY);
    }

    reply->deleteLater();
}

void RESTPlaybackController::requestStatus()
{
    sendRESTRequest(RESTAction::PLAYER_STATUS, SLOT(statusRequestCallback()));
}

void RESTPlaybackController::statusRequestCallback()
{
    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    QByteArray bArray;

    if ( !reply )
    {
        qDebug() << "network reply null";

        return;
    }

    if ( reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError )
    {
        bArray = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson( bArray );
        QJsonObject jsonObject = jsonDoc.object();

        handleStatusResponse(jsonObject);

        qDebug() << "try delete later";
        reply->deleteLater();
        qDebug() << "after delete later";
    }
    else
    {
        // if the first status request fails, there wouldn't be
        // other status requests, because there is no timer started
        // therefore we set the NODATA state (which would be anyhow the
        // state to be, if the status request fails) - this would
        // start the NODATA request timer and retry the status request
        // so objects that miss the failed signal below on the first time
        // can catch the signals in retries
        switchState(Core::NODATA);

        Q_EMIT connectionFailed();
    }


}

QNetworkReply* RESTPlaybackController::sendRESTRequest(QString request, const char *slot)
{
    return client->sendRequest(request, this, slot);
}

void RESTPlaybackController::sendRESTRequest(QString request)
{
    // reply will be automatically deleted
    client->sendRequest(request, true);
}

void RESTPlaybackController::handleCurrentMediaResonse(QJsonObject jsonCurrentMedia)
{
    if  (
            !(
                currentMediaID == jsonCurrentMedia.value("songID").toVariant().toInt()
                &&
                currentCollectionHash == jsonCurrentMedia.value("collection").toVariant().toString()
            )
        )
    {
        currentMedia = new SafriRESTClient::RESTSong(jsonCurrentMedia);

        currentMediaID = jsonCurrentMedia.value("songID").toVariant().toInt();
        currentCollectionHash = jsonCurrentMedia.value("collection").toVariant().toString();

        Q_EMIT mediaChanged(currentMedia);

        currentMedia->deleteLater();
    }
}

void RESTPlaybackController::handleStatusResponse(QJsonObject jsonStatusObject)
{
    int currentVolume;
    QVariantMap statusMap = jsonStatusObject.toVariantMap();

    mediaTotalTime = statusMap.value("mediaTotalTime").toInt();
    currentTime = statusMap.value("currentTime").toInt();
    currentVolume = statusMap.value("volume").toInt();
    bool shuffle = statusMap.value("shuffle").toBool();
    shuffleAction()->setChecked(shuffle);

    // handle eventually changed state
    switchState(statusMap.value("playState").toString());

    if (currentVolume != volume)
    {
        volume = currentVolume;
        qDebug() << "received volume changed: " << volume;
        Q_EMIT volumeChanged(volume);
    }

    QJsonObject jsonCurrentMedia = jsonStatusObject["currentMedia"].toObject();
    handleCurrentMediaResonse(jsonCurrentMedia);

    Q_EMIT update(currentTime);
}

// ****************** END NETWORK HANDLING ******************
