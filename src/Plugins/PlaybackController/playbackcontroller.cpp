#include "playbackcontroller.h"

#include "iplaylist.h"
#include "CoreData/song.h"
#include "icore.h"
#include <QStyle>
#include <QApplication>
#include <QDebug>

PlaybackController::PlaybackController()
{
    machine = new QStateMachine();
    m_play  = new QState();
    m_pause = new QState();
    m_stop  = new QState();
    m_noData = new QState();
    currentState = m_noData;
    audioBackend =  Core::ICore::audioBackend();
    if (!audioBackend)
    {
        qFatal("Null Pointer Exception in PlaybackController");
        return;
    }

    setupActions();
    setupTransitions();
    setupSignalAndSlots();



    machine->addState(m_play);
    machine->addState(m_pause);
    machine->addState(m_stop);
    machine->addState(m_noData);
    machine->setInitialState(m_noData);
    machine->start();


    connect(audioBackend, SIGNAL(update(int)), this, SLOT(audioBackendUpdate(int)));
}

void PlaybackController::setupSignalAndSlots()
{

    connect(m_play, SIGNAL(entered()), this, SLOT(playStateSlot()));
    connect(m_pause, SIGNAL(entered()), this, SLOT(pauseStateSlot()));
    connect(m_stop, SIGNAL(entered()), this, SLOT(stopStateSlot()));
    connect(audioBackend, SIGNAL(mediaFinished()), this, SLOT(currentSongFinished()));
    connect(m_nextAction,SIGNAL(triggered()) ,this, SLOT(nextActionSlot()));
    connect(m_previousAction,SIGNAL(triggered()) ,this, SLOT(previousActionSlot()));

    connect (m_noData, SIGNAL(entered()), this, SLOT(noDataSlot()));
    connect(m_shuffleAction, SIGNAL(triggered(bool)), this, SLOT(shuffleActionSlot(bool)));

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

    if(currentState == m_pause)
    {
        audioBackend->play();
        qDebug()<<"Pause->Play";
    }
    else
    {
        audioBackend->play(currentMedia->getURL());
        qDebug()<<"x -> Play";
    }
    currentState = m_play;
}

void PlaybackController::pauseStateSlot()
{
    currentState = m_pause;
    m_pauseAction->setDisabled(true);
    m_playAction->setEnabled(true);
    audioBackend->pause();
    m_playPauseAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
    stopped = false;
}

void PlaybackController::stopStateSlot()
{
    currentState = m_stop;
    m_playAction->setEnabled(true);
    m_playPauseAction->setEnabled(true);
    m_pauseAction->setEnabled(false);
    m_stopAction->setDisabled(true);
    stopped = true;
    m_playPauseAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
    audioBackend->stop();
}

void PlaybackController::currentSongFinished()
{
    if (!stopped)
    {
       m_stopAction->trigger();
       Core::Media* nextMedia = playlist->getNextMedia();
       //nextSong->ReadTags(); TODO
       if (nextMedia != currentMedia)
       {
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

}

void PlaybackController::audioBackendUpdate(int currentTime)
{
    Q_EMIT update(currentTime);
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

    }

}

void PlaybackController::shuffleActionSlot(bool value)
{
    playlist->setShuffle(value);
}


void PlaybackController::setPlaylist(Core::IPlaylist *playlist)
{
    this->playlist = playlist;
    if(playlist->getSize()>0)
    {
        currentMedia = playlist->getNextMedia();
        Q_EMIT hasData();
    }
}

Core::IPlaylist *PlaybackController::getPlaylist()
{
    qDebug() << "getPlaylist()";
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

QList<QAction *> PlaybackController::getAdditionalActions()
{
    return QList<QAction*>();

}

void PlaybackController::playMedia(Core::Media* media)
{
    // TODO: AudioEngine play song
}

void PlaybackController::seek(int playTime)
{
    audioBackend->seek(playTime);
}

void PlaybackController::setVolume(int volume)
{
    audioBackend->setVolume(volume);
}


