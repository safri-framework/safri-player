#ifndef PLAYBACKCONTROLLER_H
#define PLAYBACKCONTROLLER_H

#include "iplaybackcontroller.h"

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

        void playMedia(Core::Media* media);
};

#endif // PLAYBACKCONTROLLER_H
