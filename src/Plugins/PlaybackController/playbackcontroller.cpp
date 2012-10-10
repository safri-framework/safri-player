#include "playbackcontroller.h"

#include "iplaylist.h"
#include "CoreData/song.h"

#include <QDebug>

PlaybackController::PlaybackController()
{

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
    Core::Song *song = playlist->getCurrentPlayingSong();
    playSong(song);
}

void PlaybackController::pause()
{
    // TODO: AudioEngine pause song
}

void PlaybackController::stop()
{
    // TODO: AudioEngine stop song
}

void PlaybackController::next()
{
     Core::Song *song = playlist->getNextSong();
     playSong(song);
}

void PlaybackController::previous()
{
    Core::Song *song = playlist->getPreviousSong();
    playSong(song);
}

void PlaybackController::playSong(Core::Song *song)
{
    // TODO: AudioEngine play song
}
