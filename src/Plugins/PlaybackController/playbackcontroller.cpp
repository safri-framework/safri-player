#include "playbackcontroller.h"

#include "iplaylist.h"
#include "CoreData/song.h"
#include "icore.h"
#include <QtWidgets/QStyle>
#include <QtWidgets/QApplication>
#include <QDebug>

PlaybackController::PlaybackController()
{
    machine = new QStateMachine();
    m_play  = new QState();
    m_pause = new QState();
    m_stop  = new QState();
    m_noData = new QState();
    currentState = m_noData;
    mediaBackend = 0;

    setupActions();
    setupTransitions();
    setupSignalAndSlots();

    machine->addState(m_play);
    machine->addState(m_pause);
    machine->addState(m_stop);
    machine->addState(m_noData);
    machine->setInitialState(m_noData);
    machine->start();
}

void PlaybackController::setupSignalAndSlots()
{

    connect(m_play, SIGNAL(entered()), this, SLOT(playStateSlot()));
    connect(m_pause, SIGNAL(entered()), this, SLOT(pauseStateSlot()));
    connect(m_stop, SIGNAL(entered()), this, SLOT(stopStateSlot()));
    connect(m_nextAction,SIGNAL(triggered()) ,this, SLOT(nextActionSlot()));
    connect(m_previousAction,SIGNAL(triggered()) ,this, SLOT(previousActionSlot()));

    connect (m_noData, SIGNAL(entered()), this, SLOT(noDataSlot()));
    connect(m_shuffleAction, SIGNAL(triggered(bool)), this, SLOT(shuffleActionSlot(bool)));

}

void PlaybackController::obtainMediaBackendForMedia(Core::Media *media)
{
    Core::IMediaBackend* tmpMediaBackend = Core::ICore::getBackendForMedia(media);

    if (mediaBackend != tmpMediaBackend)
    {
        if (mediaBackend)
        {
            mediaBackend->stop();
            disconnect(mediaBackend, SIGNAL(mediaFinished()), this, SLOT(currentSongFinished()));
            disconnect(mediaBackend, SIGNAL(update(int)), this, SLOT(audioBackendUpdate(int)));
            disconnect(mediaBackend, SIGNAL(hasSeekableMedia(bool)), this, SIGNAL(hasSeekableMedia(bool)));
            disconnect(mediaBackend, SIGNAL(hasVolumeAdjustableMedia(bool)), this, SIGNAL(hasVolumeAdjustableMedia(bool)));
            disconnect(mediaBackend, SIGNAL(internalBackendStateChanged(Core::IMediaBackend::BackendState)), this, SLOT(backendStateChanged(Core::IMediaBackend::BackendState)));
        }

        mediaBackend = tmpMediaBackend;

        qDebug()<<Q_FUNC_INFO<<"HAAAALLLOOOO??"<<mediaBackend;
        if (mediaBackend)
        {
            connect(mediaBackend, SIGNAL(mediaFinished()), this, SLOT(currentSongFinished()));
            connect(mediaBackend, SIGNAL(update(int)), this, SLOT(audioBackendUpdate(int)));
            connect(mediaBackend, SIGNAL(hasSeekableMedia(bool)), this, SIGNAL(hasSeekableMedia(bool)));
            connect(mediaBackend, SIGNAL(hasVolumeAdjustableMedia(bool)), this, SIGNAL(hasVolumeAdjustableMedia(bool)));
            connect(mediaBackend, SIGNAL(internalBackendStateChanged(Core::IMediaBackend::BackendState)), this, SLOT(backendStateChanged(Core::IMediaBackend::BackendState)));
        }
    }
}

void PlaybackController::setupActions()
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

}

void PlaybackController::setupTransitions()
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

void PlaybackController::playStateSlot()
{
    m_shuffleAction->setDisabled(false);
    m_nextAction->setDisabled(false);
    m_previousAction->setDisabled(false);
    m_playPauseAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPause));
    stopped = false;
    m_stopAction->setDisabled(false);
    m_playPauseAction->setDisabled(false);
    m_playAction->setDisabled(true);
    m_pauseAction->setDisabled(false);

    currentMedia = playlist->getCurrentMedia();

    if(currentState == m_pause)
    {
        if (!mediaBackend)
        {
            return;
        }
        mediaBackend->play();
        qDebug()<<"Pause->Play";
    }
    else
    {

        obtainMediaBackendForMedia(currentMedia);

        if (!mediaBackend)
        {
            return;
        }

        mediaBackend->play(currentMedia->getURL());
        Q_EMIT mediaChanged(currentMedia);
        qDebug()<<"x -> Play";
    }
    currentState = m_play;
    Q_EMIT stateChanged(Core::PLAY);
}

void PlaybackController::pauseStateSlot()
{
    qDebug()<<"PAUSE state";
    currentState = m_pause;
    Q_EMIT stateChanged(Core::PAUSE);
    m_pauseAction->setDisabled(true);
    m_playAction->setEnabled(true);
    if (mediaBackend)
    {
        mediaBackend->pause();
    }
    m_playPauseAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
    stopped = false;
}

void PlaybackController::stopStateSlot()
{
    currentState = m_stop;
    Q_EMIT stateChanged(Core::STOP);
    m_playAction->setEnabled(true);
    m_playPauseAction->setEnabled(true);
    m_pauseAction->setEnabled(false);
    m_stopAction->setDisabled(true);
    stopped = true;
    m_playPauseAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));

    if (mediaBackend)
    {
        mediaBackend->stop();
    }
}

void PlaybackController::currentSongFinished()
{
    qDebug()<<playlist->getCurrentMediaPosition();
    qDebug()<<playlist->getSize();
    if (!stopped)
    {
       m_stopAction->trigger();

       //nextSong->ReadTags(); TODO


       //if (nextMedia != currentMedia) // Was passiert, wenn zweimal der gleiche Zeiger in der PLaylist liegt? Fixversuch:
       if(playlist->getCurrentMediaPosition()+1 < playlist->getSize()) //check obs noch mit random funzt
       {
           Core::Media* nextMedia = playlist->getNextMedia();
           qDebug()<<"nextSong";
           currentMedia = nextMedia;
           m_playPauseAction->trigger();          
       }
       else
       {
           m_stopAction->trigger();           
       }
    }
}


void PlaybackController::noDataSlot()
{
    m_shuffleAction->setDisabled(true);
    m_stopAction->setDisabled(true);
    m_nextAction->setDisabled(true);
    m_previousAction->setDisabled(true);
    m_playPauseAction->setDisabled(true);
    Q_EMIT stateChanged(Core::NODATA);
}

void PlaybackController::audioBackendUpdate(int currentTime)
{
    Q_EMIT update(currentTime);
}

void PlaybackController::backendStateChanged(Core::IMediaBackend::BackendState state)
{
    qDebug()<<"state"<< Q_FUNC_INFO;
    switch (state)
    {
        case Core::IMediaBackend::BUFFERING:
            qDebug()<<"BUFFERING";
            Q_EMIT stateChanged(Core::BUFFERING);
            break;
        case Core::IMediaBackend::PLAYING:
            Q_EMIT stateChanged(Core::PLAY);

    }
}

void PlaybackController::nextActionSlot()
{
    Core::Media *media = playlist->getNextMedia();

    if (media)
    {
       m_stopAction->trigger();
       currentMedia = media;
       m_playPauseAction->trigger();
    }
}

void PlaybackController::previousActionSlot()
{
    Core::Media *media = playlist->getPreviousMedia();
    if (media)
    {
        m_stopAction->trigger();
        currentMedia = media;
        m_playPauseAction->trigger();
        Q_EMIT mediaChanged(currentMedia);
    }

}

void PlaybackController::shuffleActionSlot(bool value)
{
    if(playlist)
        playlist->setShuffle(value);

}

void PlaybackController::setPlaylist(QSharedPointer<Core::IPlaylist> playlist)
{
    playlist->setShuffle(m_shuffleAction->isChecked());
    this->playlist = playlist;
    if(playlist->getSize()>0)
    {
        currentMedia = playlist->getCurrentMedia();
        Q_EMIT hasData();
    }
    else
    {
        qDebug()<<"leere Playliste";
    }
    Q_EMIT newPlaylistInstalled(playlist);
}

QSharedPointer<Core::IPlaylist> PlaybackController::getPlaylist()
{
    return this->playlist;
}


QAction* PlaybackController::playPauseAction()
{
    return this->m_playPauseAction;
}

QAction* PlaybackController::playAction()
{
    return this->m_playAction;
}

QAction* PlaybackController::pauseAction()
{
    return this->m_pauseAction;
}

QAction* PlaybackController::stopAction()
{
    return this->m_stopAction;
}

QAction* PlaybackController::nextAction()
{
    return this->m_nextAction;
}

QAction* PlaybackController::previousAction()
{
    return this->m_previousAction;
}

QAction *PlaybackController::shuffleAction()
{
    return this->m_shuffleAction;
}

QList<QAction *> PlaybackController::getAdditionalActions()
{
    return QList<QAction*>();

}

int PlaybackController::getMediaTotalTime()
{
    if (mediaBackend)
    {
        return mediaBackend->getTotalTime();
    }

    return -1;
}

int PlaybackController::getVolume()
{
    if (mediaBackend)
    {
        return mediaBackend->getVolume();
    }

    return -1;
}

void PlaybackController::seek(int playTime)
{
    if (mediaBackend)
    {
        mediaBackend->seek(playTime);
    }
}

void PlaybackController::setVolume(int volume)
{
    if (mediaBackend)
    {
        mediaBackend->setVolume(volume);
    }
}


