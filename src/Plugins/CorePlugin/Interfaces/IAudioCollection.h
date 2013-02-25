#ifndef IAUDIOCOLLECTION_H
#define IAUDIOCOLLECTION_H
#include "../CorePlugin_global.h"
#include "IMediaCollection.h"
#include "../CoreData/song.h"
#include "../CoreData/album.h"
#include "../CoreData/artist.h"
#include "../CoreData/genre.h"

namespace Core
{
    class COREPLUGINSHARED_EXPORT IAudioCollection : public Core::IMediaCollection
    {
        Q_OBJECT
        public:

            explicit IAudioCollection(QObject *parent = 0);
            ~IAudioCollection();

            virtual QList<Core::Song*> getSongs() = 0;
            virtual Core::Song* getSongByID(int id) = 0;
            virtual QList<Core::Song*> getSongsByName(QString name) = 0;
            virtual Core::Song* getSongByPath(QString path) = 0;

            virtual QList<Core::Artist*> getArtists() = 0;
            virtual QList<Core::Artist*> getArtistsByName(QString name) = 0;
            virtual Core::Artist* getArtistByID(int id) = 0;

            virtual QList<Core::Album*> getAlbums() = 0;
            virtual QList<Core::Album*> getAlbumsByName(QString name) = 0;
            virtual Core::Album* getAlbumByID(int id) = 0;

            virtual QList<Core::Genre*> getGenres() = 0;
            virtual QList<Core::Genre*> getGenresByName(QString name) = 0;
            virtual Core::Genre* getGenreByID(int id) = 0;
    };
}
Q_DECLARE_INTERFACE(Core::IAudioCollection, "Core::IAudioCollection")

#endif // IAUDIOCOLLECTION_H
