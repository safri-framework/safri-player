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

RESTPlaybackController::RESTPlaybackController(QString RESTLocation, QObject *parent) :
    statusTimer(new QTimer(this))
{
    this->setParent(parent);

    setupActions();
    setupStateMachine();

    client = new RESTClient(RESTLocation, this);

    connect(statusTimer, SIGNAL(timeout()), this, SLOT(statusTimerShot()));
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

    // called by state machine transitions
    void RESTPlaybackController::playStateSlot()
    {
        //qDebug() << "PLAY";
        sendRESTRequest(RESTAction::PLAYER_PLAY, SLOT(playRequestCallback()));
    }

    // called by state machine transitions
    void RESTPlaybackController::pauseStateSlot()
    {
        //qDebug() << "PAUSE";
        sendRESTRequest(RESTAction::PLAYER_PAUSE, SLOT(pauseRequestCallback()));
    }

    // called by state machine transitions
    void RESTPlaybackController::stopStateSlot()
    {
        //qDebug() << "STOP";
    }

    // called by state machine transitions
    void RESTPlaybackController::noDataStateSlot()
    {
        //qDebug() << "NoDATA";
    }

    // called directly by the actions triggered signal
    void RESTPlaybackController::nextActionSlot()
    {
        //qDebug() << "NEXT";
        sendRESTRequest(RESTAction::PLAYER_NEXT, SLOT(nextRequestCallback()));
    }

    // called directly by the actions triggered signal
    void RESTPlaybackController::previousActionSlot()
    {
        //qDebug() << "PREVIOUS";
        sendRESTRequest(RESTAction::PLAYER_PREVIOUS, SLOT(previousRequestCallback()));
    }

    // called directly by the actions triggered signal
    void RESTPlaybackController::shuffleActionSlot(bool value)
    {
    }

    void RESTPlaybackController::currentSongFinished()
    {
    }

    void RESTPlaybackController::noDataSlot()
    {
        // TODO: unnecessarily needed by interface
        // replaced here by noDataStateSlot
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

// ***** END ACTUAL WORK IS DONE HERE *****

// ****************** END INTERFACE IMPLEMENTATION ******************

void RESTPlaybackController::setupActions()
{
    m_shuffleAction = new QAction(QIcon(":icons/ressources/shuffle_icon.png"), tr("Shuffle"), this);
    m_shuffleAction->setCheckable(true);
    m_shuffleAction->setChecked(false);
    m_playPauseAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    m_playPauseAction->setShortcut(tr("Ctrl+P"));
    m_playPauseAction->setDisabled(false);
    m_stopAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    m_stopAction->setShortcut(tr("Ctrl+S"));
    m_stopAction->setDisabled(false);
    m_nextAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaSkipForward), tr("Next"), this);
    m_nextAction->setShortcut(tr("Ctrl+N"));
    m_previousAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaSkipBackward), tr("Previous"), this);
    m_previousAction->setShortcut(tr("Ctrl+R"));

    m_pauseAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
    m_playAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);

    // following signals are connected directly to it's corresponding slots
    // all other action triggered signals are connected to the state machine transitions
    // the actual event slots will then be called from the state changes
    connect(m_nextAction,SIGNAL(triggered()) ,this, SLOT(nextActionSlot()));
    connect(m_previousAction,SIGNAL(triggered()) ,this, SLOT(previousActionSlot()));
    connect(m_shuffleAction, SIGNAL(triggered(bool)), this, SLOT(shuffleActionSlot(bool)));
}

void RESTPlaybackController::setupStateMachine()
{
    machine = new QStateMachine();
    m_play  = new QState();
    m_pause = new QState();
    m_stop  = new QState();
    m_noData = new QState();

    currentState = m_noData;

    connect(m_play, SIGNAL(entered()), this, SLOT(playStateSlot()));
    connect(m_pause, SIGNAL(entered()), this, SLOT(pauseStateSlot()));
    connect(m_stop, SIGNAL(entered()), this, SLOT(stopStateSlot()));
    connect (m_noData, SIGNAL(entered()), this, SLOT(noDataStateSlot()));

    setupStateTransitions();

    machine->addState(m_play);
    machine->addState(m_pause);
    machine->addState(m_stop);
    machine->addState(m_noData);

    // TODO: initState noData
    machine->setInitialState(m_stop);
    machine->start();
}

void RESTPlaybackController::setupStateTransitions()
{
    m_play  ->addTransition(m_playPauseAction, SIGNAL(triggered()), m_pause);
    m_play  ->addTransition(m_pauseAction, SIGNAL(triggered()), m_pause);
    m_pause ->addTransition(m_playPauseAction, SIGNAL(triggered()), m_play);

    m_pause ->addTransition(m_playAction, SIGNAL(triggered()), m_play);

    m_pause ->addTransition(m_stopAction, SIGNAL(triggered()), m_stop);
    m_play  ->addTransition(m_stopAction, SIGNAL(triggered()), m_stop);
    m_stop  ->addTransition(m_playPauseAction, SIGNAL(triggered()), m_play);

    m_stop  ->addTransition(m_playAction, SIGNAL(triggered()), m_play);

    m_pause ->addTransition(m_nextAction, SIGNAL(triggered()),m_play);
    m_pause ->addTransition(m_previousAction, SIGNAL(triggered()),m_play);
    m_stop  ->addTransition(m_nextAction, SIGNAL(triggered()), m_play);
    m_stop  ->addTransition(m_previousAction, SIGNAL(triggered()), m_play);
    m_noData->addTransition(m_playPauseAction, SIGNAL(triggered()), m_play);
    m_noData->addTransition(this, SIGNAL(hasData()),m_stop);
}

// ****************** BEGIN NETWORK HANDLING ******************

void RESTPlaybackController::playRequestCallback()
{
    //qDebug() << "playRequestCallback";
    statusTimer->start(SATUS_TIMER_INTERVAL);

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
        QJsonObject jsonCurrentMedia = jsonObject["currentMedia"].toObject();

        handleCurrentMediaResonse(jsonCurrentMedia);

        m_shuffleAction->setDisabled(false);
        m_nextAction->setDisabled(false);
        m_previousAction->setDisabled(false);
        m_playPauseAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPause));
        m_stopAction->setDisabled(false);
        m_playPauseAction->setDisabled(false);
        m_playAction->setDisabled(true);
        m_pauseAction->setDisabled(false);

        Q_EMIT stateChanged(Core::PLAY);
    }
}

void RESTPlaybackController::pauseRequestCallback()
{
    //qDebug() << "pauseRequestCallback";
    statusTimer->stop();

    m_pauseAction->setDisabled(true);
    m_playAction->setEnabled(true);
    m_playPauseAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));

    Q_EMIT stateChanged(Core::PAUSE);
}

void RESTPlaybackController::stopRequestCallback()
{
    //qDebug() << "stopRequestCallback";
    statusTimer->stop();

    m_playAction->setEnabled(true);
    m_playPauseAction->setEnabled(true);
    m_pauseAction->setEnabled(false);
    m_stopAction->setDisabled(true);

    Q_EMIT stateChanged(Core::STOP);
}

void RESTPlaybackController::nextRequestCallback()
{
    //qDebug() << "nextRequestCallback";
    statusTimer->start(SATUS_TIMER_INTERVAL);

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
        QJsonObject jsonCurrentMedia = jsonObject["currentMedia"].toObject();

        handleCurrentMediaResonse(jsonCurrentMedia);
    }
}

void RESTPlaybackController::previousRequestCallback()
{
    //qDebug() << "previousRequestCallback";
    statusTimer->start(SATUS_TIMER_INTERVAL);

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
        QJsonObject jsonCurrentMedia = jsonObject["currentMedia"].toObject();

        handleCurrentMediaResonse(jsonCurrentMedia);
    }
}

void RESTPlaybackController::statusTimerShot()
{
    sendRESTRequest(RESTAction::PLAYER_STATUS, SLOT(statusRequestCallback()));
}

void RESTPlaybackController::statusRequestCallback()
{
    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    QByteArray bArray;
    int currentVolume;

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

        //qDebug() << bArray;
        //qDebug() << jsonObject.toVariantMap().value("currentTime").toString();
        mediaTotalTime = jsonObject.toVariantMap().value("mediaTotalTime").toInt();
        currentTime = jsonObject.toVariantMap().value("currentTime").toInt();
        currentVolume = jsonObject.toVariantMap().value("volume").toInt();

        if (currentVolume != volume)
        {
            volume = currentVolume;
            qDebug() << "received volume changed: " << volume;
            Q_EMIT volumeChanged(volume);
        }

        QJsonObject jsonCurrentMedia = jsonObject["currentMedia"].toObject();
        handleCurrentMediaResonse(jsonCurrentMedia);

        Q_EMIT update(currentTime);
    }
}

QNetworkReply* RESTPlaybackController::sendRESTRequest(QString request, const char *slot)
{
    return client->sendRequest(request, this, slot);
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

        qDebug() << "mediaChanged";
        Q_EMIT mediaChanged(currentMedia);

        currentMedia->deleteLater();
    }
}

// ****************** END NETWORK HANDLING ******************
