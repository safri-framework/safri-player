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






}

void PlaybackController::setupSignalAndSlots()
{

    connect(m_play, SIGNAL(entered()), this, SLOT(playStateSlot()));
    connect(m_pause, SIGNAL(entered()), this, SLOT(pauseStateSlot()));
    connect(m_stop, SIGNAL(entered()), this, SLOT(stopStateSlot()));
    connect(audioBackend, SIGNAL(mediaFinished()), this, SLOT(currentSongFinished()));
    connect(nextAction,SIGNAL(triggered()) ,this, SLOT(nextActionSlot()));
    connect(previousAction,SIGNAL(triggered()) ,this, SLOT(previousActionSlot()));

    connect (m_noData, SIGNAL(entered()), this, SLOT(noDataSlot()));
    connect(shuffleAction, SIGNAL(triggered(bool)), this, SLOT(shuffleActionSlot(bool)));

}
void PlaybackController::setupActions()
{
    shuffleAction = new QAction(QIcon(":icons/ressources/shuffle_icon.png"), tr("Shuffle"), this);
    shuffleAction->setCheckable(true);
    shuffleAction->setChecked(false);
    playAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    playAction->setShortcut(tr("Ctrl+P"));
    playAction->setDisabled(false);
    stopAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    stopAction->setShortcut(tr("Ctrl+S"));
    stopAction->setDisabled(false);
    nextAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaSkipForward), tr("Next"), this);
    nextAction->setShortcut(tr("Ctrl+N"));
    previousAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MediaSkipBackward), tr("Previous"), this);
    previousAction->setShortcut(tr("Ctrl+R"));
}

void PlaybackController::setupTransitions()
{
    m_play  ->addTransition(playAction, SIGNAL(triggered()), m_pause);
    m_pause ->addTransition(playAction, SIGNAL(triggered()), m_play);
    m_pause ->addTransition(stopAction, SIGNAL(triggered()), m_stop);
    m_play  ->addTransition(stopAction, SIGNAL(triggered()), m_stop);
    m_stop  ->addTransition(playAction, SIGNAL(triggered()), m_play);
    m_pause ->addTransition(nextAction, SIGNAL(triggered()),m_play);
    m_pause ->addTransition(previousAction, SIGNAL(triggered()),m_play);
    m_stop  ->addTransition(nextAction, SIGNAL(triggered()), m_play);
    m_stop  ->addTransition(previousAction, SIGNAL(triggered()), m_play);
    m_noData->addTransition(playAction, SIGNAL(triggered()), m_play);
}

void PlaybackController::playStateSlot()
{

    currentState = m_play;
    shuffleAction->setDisabled(false);
    nextAction->setDisabled(false);
    previousAction->setDisabled(false);
    playAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPause));
    stopped = false;
    stopAction->setDisabled(false);
    playAction->setDisabled(false);
    audioBackend->play(currentMedia->getURL());
}

void PlaybackController::pauseStateSlot()
{
    currentState = m_pause;
    audioBackend->pause();
    playAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
    stopped = false;
}

void PlaybackController::stopStateSlot()
{
    currentState = m_stop;
    stopAction->setDisabled(true);
    stopped = true;
    playAction->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
    audioBackend->stop();
}

void PlaybackController::currentSongFinished()
{
    if (!stopped)
    {
       stopAction->trigger();
       Core::Media* nextMedia = playlist->getNextMedia();
       //nextSong->ReadTags(); TODO
       if (nextMedia != currentMedia)
       {
           currentMedia = nextMedia;
           playAction->trigger();

       }
       else
       {
           stopAction->trigger();
       }
    }
}


void PlaybackController::noDataSlot()
{
    shuffleAction->setDisabled(true);
    stopAction->setDisabled(true);
    nextAction->setDisabled(true);
    previousAction->setDisabled(true);
    playAction->setDisabled(true);

}

void PlaybackController::nextActionSlot()
{

    Core::Media *media = playlist->getNextMedia();

    if (media)
    {

       stopAction->trigger();
       currentMedia = media;
       playAction->trigger();
    }
}

void PlaybackController::previousActionSlot()
{
    Core::Media *media = playlist->getPreviousMedia();
    if (media)
    {
        stopAction->trigger();
        currentMedia = media;
        playAction->trigger();

    }

}

void PlaybackController::shuffleActionSlot(bool value)
{
    playlist->setShuffle(value);
}


void PlaybackController::setPlaylist(Core::IPlaylist *playlist)
{
    this->playlist = playlist;
}

Core::IPlaylist *PlaybackController::getPlaylist()
{
    qDebug() << "getPlaylist()";
    return this->playlist;
}

void PlaybackController::play()
{
    if (!(currentState == m_play))
    {
        playAction->trigger();
    }
}

void PlaybackController::pause()
{
    if (currentState == m_play)
    {
        playAction->trigger();
    }

}

void PlaybackController::stop()
{
    stopAction->trigger();
}

void PlaybackController::next()
{

    nextAction->trigger();

}

void PlaybackController::previous()
{
    previousAction->trigger();
}

void PlaybackController::playMedia(Core::Media* media)
{
    // TODO: AudioEngine play song
}

void PlaybackController::seek(int playTime)
{
}


