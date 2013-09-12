#ifndef AUDIOSQLSTORAGE_H
#define AUDIOSQLSTORAGE_H

#include "AudioSQLStorage_global.h"
#include "Interfaces/IMediaCollectionStorage.h"
#include <QUrl>
#include <QSqlQuery>
#include <QMap>

class ISQLStorage;

namespace Core
{
    class IAudioCollection;
}

class AUDIOSQLSTORAGESHARED_EXPORT AudioSQLStorage : public Core::IMediaCollectionStorage
{
    Q_OBJECT
    public:

        explicit AudioSQLStorage(QUrl url, QObject *parent = 0);
        ~AudioSQLStorage();


        virtual Core::IMediaCollection*     loadMediaCollection();
        virtual bool                        saveMediaCollection(Core::IMediaCollection *collection);
        virtual QString                     getStorageType();

    private:

        bool                                checkIfDatabaseExists();
        bool                                checkDatabaseVersion();
        bool                                loadGenres();
        bool                                loadArtists();
        QMap<int, int>                      loadArtistToAlbumMap();
        bool                                loadAlbums();
        bool                                loadSongs();

        bool                                createDatabase();
        bool                                saveGenres();
        bool                                saveArtists();
        bool                                saveAlbums();
        bool                                saveSongs();

    private:

        QUrl                    url;
        ISQLStorage*            sqlStorage;
        QSqlQuery               query;
        Core::IAudioCollection* audioCollection;
};

#endif // AUDIOSQLSTORAGE_H
