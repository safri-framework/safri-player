#ifndef PLAYLISTFACTORY_H
#define PLAYLISTFACTORY_H

#include <QObject>
#include "Playlist_global.h"
#include "Interfaces/IPlaylistFactory.h"

class PLAYLISTSHARED_EXPORT PlaylistFactory : public Core::IPlaylistFactory
{
    Q_OBJECT
    public:

        PlaylistFactory();

        virtual Core::IPlaylist* createPlaylist();
};

#endif // PLAYLISTFACTORY_H
