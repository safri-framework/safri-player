#include "playlistfactory.h"
#include "playlist.h"

PlaylistFactory::PlaylistFactory()
{
}

Core::IPlaylist *PlaylistFactory::createPlaylist()
{
    return new Playlist(this);
}
