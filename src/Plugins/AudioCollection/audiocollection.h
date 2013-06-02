#ifndef AUDIOCOLLECTION_H
#define AUDIOCOLLECTION_H

#include "Interfaces/IAudioCollection.h"
#include <QUrl>
#include <QReadWriteLock>
#include "CoreData/dataitem.h"
#include "CoreData/media.h"
#include <QMap>

using namespace Core;

class AudioCollection : public Core::IAudioCollection
{
    friend class AudioCollectionBuilder;
    Q_OBJECT


    public:
        explicit AudioCollection(QString name, QUrl url = QUrl());
        ~AudioCollection();

         // ------------------- Media Collection Interface

        QList<DataItem*> getByName(DataItem::DATA_ITEM_TYPE type, QString name);
        QList<Media*> getByPath(DataItem::DATA_ITEM_TYPE type, QString path);
        DataItem* getByID(DataItem::DATA_ITEM_TYPE type, int id);
        QList<DataItem*> getDataItems(DataItem::DATA_ITEM_TYPE type);
        QList<Media*> getMedia();
        QString getName();
        QUrl getAssetFolderPath(QString subfolder);
        bool isAvailable();
        void lockForRead();
        void lockForWrite();
        void unlock();

        //path to Music root Folder
        QUrl getRootPath();
        QString getHash();

        //path to *.db File
        QUrl getDatabaseLocation();
        void setDatabaseLocation(QUrl url);

        InfoContainer* getInfoContainerByName(QString name);
        QString getContentType();
        void addMedia(MediaInfoContainer container);

        // ------------------- Audio Collection Interface

        QList<Core::Song*> getSongs();
        Core::Song* getSongByID(int id);
        QList<Core::Song*> getSongsByName(QString name);
        Core::Song* getSongByPath(QString path);
        Core::Song* newSong(QString name, int year, QUrl url);
        void removeSong(Song* song);

        QList<Core::Artist*> getArtists();
        QList<Core::Artist*> getArtistsByName(QString name);
        Core::Artist* getArtistByID(int id);
        Core::Artist* newArtist(QString name);
        void removeArtist(Artist* artist);

        QList<Core::Album*> getAlbums();
        QList<Core::Album*> getAlbumsByName(QString name);
        Core::Album* getAlbumByID(int id);
        Core::Album* newAlbum(QString name);
        void removeAlbum(Album* album);

        QList<Core::Genre*> getGenres();
        QList<Core::Genre*> getGenresByName(QString name);
        Core::Genre* getGenreByID(int id);
        Core::Genre* newGenre(QString genre);
        void removeGenre(Genre* genre);

        void insertGenre(Core::Genre* genre);
        void insertArtist(Core::Artist* artist);
        void insertAlbum(Core::Album* album);
        void insertSong(Core::Song* song);

    private:

        QList<Song*>* m_songList;
        QList<Artist*>* m_artistList;
        QList<Album*>* m_albumList;
        QList<Genre*>* m_genreList;
        QMap<int, Song*>* m_IDtoSongMap;
        QMap<QString, Song*>* m_PathToSongMap;
        QMap<int, Artist*>* m_IDtoArtistMap;
        QMap<int, Album*>* m_IDtoAlbumMap;
        QMap<int, Genre*>* m_IDtoGenreMap;


        QMap<QString, Song*>* m_nameToSongMap;
        QMap<QString, Artist*>* m_nameToArtistMap;
        QMap<QString, Album*>* m_nameToAlbumMap;
        QMap<QString, Genre*>* m_nameToGenreMap;

        QString m_name;
        QUrl m_rootPath;
        QUrl m_databaseLocation;
        QString m_hash;
        QReadWriteLock m_lock;

        int newAlbumID();
        int newArtistID();
        int newGenreID();
        int newSongID();

        //will be initialized by AudioCollection Builder via friend-relationship
        int currentAlbumID;
        int currentArtistID;
        int currentGenreID;
        int currentSongID;


};

#endif // AUDIOCOLLECTION_H
