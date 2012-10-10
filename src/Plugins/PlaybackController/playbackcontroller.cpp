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
    Core::Media *media = playlist->getCurrentMedia();
    playMedia(media);
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
     Core::Media *media = playlist->getNextMedia();

     if (media)
     {
        playMedia(media);
     }
}

void PlaybackController::previous()
{
    Core::Media *media = playlist->getPreviousMedia();

    if (media)
    {
        playMedia(media);
    }
}

void PlaybackController::playMedia(Core::Media* media)
{
    // TODO: AudioEngine play song
}
