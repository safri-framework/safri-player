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

        QList<Core::AlbumArtist*> getAlbumArtists();
        QList<Core::AlbumArtist*> getAlbumArtistsByName(QString name);
        Core::AlbumArtist* getAlbumArtistByID(int id);
        Core::AlbumArtist* newAlbumArtist(QString name);
        void removeAlbumArtist(AlbumArtist* albumArtist);


        void insertGenre(Core::Genre* genre);
        void insertArtist(Core::Artist* artist);
        void insertAlbum(Core::Album* album);
        void insertSong(Core::Song* song);
        void insertAlbumArtist(Core::AlbumArtist* albumArtist);

    private:

        QList<Song*>* m_songList;
        QList<Artist*>* m_artistList;
        QList<Album*>* m_albumList;
        QList<Genre*>* m_genreList;
        QList<AlbumArtist*>* m_albumArtistList;

        QMap<int, Song*>* m_IDtoSongMap;
        QMap<QString, Song*>* m_PathToSongMap;
        QMap<int, Artist*>* m_IDtoArtistMap;
        QMap<int, Album*>* m_IDtoAlbumMap;
        QMap<int, Genre*>* m_IDtoGenreMap;
        QMap<int, AlbumArtist*>* m_IDtoAlbumArtistMap;


        QMap<QString, Song*>* m_nameToSongMap;
        QMap<QString, Artist*>* m_nameToArtistMap;
        QMap<QString, Album*>* m_nameToAlbumMap;
        QMap<QString, Genre*>* m_nameToGenreMap;
        QMap<QString, AlbumArtist*>* m_nameToAlbumArtistMap;

        QString m_name;
        QUrl m_rootPath;
        QUrl m_databaseLocation;
        QString m_hash;
        QReadWriteLock m_lock;

        int newAlbumID();
        int newAlbumArtistID();
        int newArtistID();
        int newGenreID();
        int newSongID();

        //will be initialized by AudioCollection Builder via friend-relationship
        int currentAlbumID;
        int currentArtistID;
        int currentGenreID;
        int currentSongID;
        int currentAlbumArtistID;


};

#endif // AUDIOCOLLECTION_H
