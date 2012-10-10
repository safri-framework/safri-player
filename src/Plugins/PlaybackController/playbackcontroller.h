#ifndef PLAYBACKCONTROLLER_H
#define PLAYBACKCONTROLLER_H

#include "iplaybackcontroller.h"

namespace Core { class Song; } // forward declaration

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

        void playSong(Core::Song* song);
};

#endif // PLAYBACKCONTROLLER_H
