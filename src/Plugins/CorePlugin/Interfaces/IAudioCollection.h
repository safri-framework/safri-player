#ifndef IAUDIOCOLLECTION_H
#define IAUDIOCOLLECTION_H
#include "../CorePlugin_global.h"
#include "IMediaCollection.h"
#include "../CoreData/Audio.h"

namespace Core
{
    class IMediaCollectionStorage;

    class COREPLUGINSHARED_EXPORT IAudioCollection : public Core::IMediaCollection
    {
        Q_OBJECT
        public:

            explicit IAudioCollection(QObject *parent = 0);
            ~IAudioCollection();

            virtual QList<Core::Song*>          getSongs() = 0;
            virtual Core::Song*                 getSongByID(int id) = 0;
            virtual QList<Core::Song*>          getSongsByName(QString name) = 0;
            virtual Core::Song*                 getSongByPath(QString path) = 0;

            virtual QList<Core::Artist*>        getArtists() = 0;
            virtual QList<Core::Artist*>        getArtistsByName(QString name) = 0;
            virtual Core::Artist*               getArtistByID(int id) = 0;

            virtual QList<Core::Album*>         getAlbums() = 0;
            virtual QList<Core::Album*>         getAlbumsByName(QString name) = 0;
            virtual Core::Album*                getAlbumByID(int id) = 0;

            virtual QList<Core::Genre*>         getGenres() = 0;
            virtual QList<Core::Genre*>         getGenresByName(QString name) = 0;
            virtual Core::Genre*                getGenreByID(int id) = 0;

            virtual QList<Core::AlbumArtist*>   getAlbumArtists() = 0;
            virtual QList<Core::AlbumArtist*>   getAlbumArtistsByName(QString name) = 0;
            virtual Core::AlbumArtist*          getAlbumArtistByID(int id) = 0;

        void removeAlbumArtist(AlbumArtist* albumArtist);

            virtual void                    insertGenre(Core::Genre* genre) = 0;
            virtual void                    insertArtist(Core::Artist* genre) = 0;
            virtual void                    insertAlbum(Core::Album* album) = 0;
            virtual void                    insertSong(Core::Song* song) = 0;
            virtual void                    insertAlbumArtist(Core::AlbumArtist* albumArtist) = 0;

    signals:

            void newAlbumInserted(Core::Album*);
            void newArtistInserted(Core::Artist*);
            void newGenreInserted(Core::Genre*);
            void newSongInserted(Core::Song*);
            void newAlbumArtistInserted(Core::AlbumArtist*);
    };
}
Q_DECLARE_INTERFACE(Core::IAudioCollection, "Core::IAudioCollection")

#endif // IAUDIOCOLLECTION_H
