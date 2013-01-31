#include "playlistfactory.h"
#include "playlist.h"

PlaylistFactory::PlaylistFactory()
{
}

QSharedPointer<Core::IPlaylist> PlaylistFactory::createPlaylist()
{
    return QSharedPointer<IPlaylist>((IPlaylist*) new Playlist(this));
}
