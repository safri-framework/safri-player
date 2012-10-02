#ifndef PLAYBACKCONTROLLER_H
#define PLAYBACKCONTROLLER_H

#include "iplaybackcontroller.h"

class Song;

class PlaybackController : public Core::IPlaybackController
{
    Q_OBJECT
    Q_INTERFACES(Core::IPlaybackController)
    public:

        PlaybackController();

        void setPlaylist(Core::IPlaylist* playlist);
        Core::IPlaylist* getPlaylist();

        void play();
        void pause();
        void stop();
        void next();
        void previous();

    protected:

        Core::IPlaylist *playlist;

        void playSong(Song* song);
};

#endif // PLAYBACKCONTROLLER_H
