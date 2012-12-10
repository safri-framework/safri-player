#include "audiocollectionbuilder.h"
#include <Interfaces/ITableModel.h>
#include <QList>

AudioCollectionBuilder::AudioCollectionBuilder(QObject *parent) :
    IMediaCollectionBuilder(parent)
{
}

IMediaCollection *AudioCollectionBuilder::buildMediaCollection(IStorageAdapter *storageAdapter, MetaInfo *metaInfoAdapter)
{
    //QString name = metaInfoAdapter->getDBName();
    QString name;

    if(!metaInfoAdapter)
    {
        name = "SafriInitialCollection";
    }
    else
    {

    }

    AudioCollection* audioCollection = new AudioCollection(name);

    buildGenres(storageAdapter, audioCollection);
    buildArtists(storageAdapter, audioCollection);
    buildAlbums(storageAdapter, audioCollection);
    buildSongs(storageAdapter, audioCollection);

    return audioCollection;
}

void AudioCollectionBuilder::storeMediaCollection(IMediaCollection *mediaCollection, IStorageAdapter *storageAdapter)
{

}

void AudioCollectionBuilder::buildGenres(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
    ITableModel* table = storageAdapter->loadTableForDataItemType(DataItem::GENRE);
    int idIndex = table->indexOfColumn("id");
    int nameIndex = table->indexOfColumn("genre");
    int numberOfGenres = table->rowCount();
    int latestID = 0;
    int id;
    QString name;

    for (int i = 0; i <numberOfGenres; i++)
    {
        id = table->data(table->index(i, idIndex)).toInt();

        if (id > latestID)
        {
            latestID = id;
        }

        name = table->data(table->index(i, nameIndex)).toString();
        mediaCollection->insertGenre(new Genre(id, name, mediaCollection));
    }

    delete table;
    mediaCollection->currentGenreID = latestID;
}

void AudioCollectionBuilder::buildArtists(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
    ITableModel* table = storageAdapter->loadTableForDataItemType(DataItem::ARTIST);
    int idIndex = table->indexOfColumn("id");
    int nameIndex = table->indexOfColumn("artist");
    int numberOfArtist = table->rowCount();
    int latestID = 0;
    int id;
    QString name;

    for (int i = 0; i < numberOfArtist; i++)
    {
        id = table->data(table->index(i, idIndex)).toInt();
        if (id > latestID)
        {
            latestID = id;
        }
        name = table->data(table->index(i, nameIndex)).toString();
        mediaCollection->insertArtist(new Artist(id, name, mediaCollection));
    }

    mediaCollection->currentArtistID = latestID;
    delete table;
}

QMultiMap<int, int> AudioCollectionBuilder::loadArtistToAlbumMap(IStorageAdapter *storageAdapter)
{
    ITableModel* table = storageAdapter->loadTable("ArtistToAlbum");
    QMultiMap<int, int> artistToAlbumMap;
    int rows = table->rowCount();

    int artistID, albumID;
    int artistIndex, albumIndex;

    artistIndex = table->indexOfColumn("artist_id");
    albumIndex = table->indexOfColumn("album_id");

    for (int i = 0; i < rows; i++)
    {
        artistID = table->data(table->index(i, artistIndex)).toInt();
        albumID = table->data(table->index(i, albumIndex)).toInt();

        artistToAlbumMap.insert(albumID, artistID);
    }

    delete table;

    return artistToAlbumMap;
}

void AudioCollectionBuilder::buildAlbums(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
    QMultiMap<int, int> artistToAlbumMap = loadArtistToAlbumMap(storageAdapter);
    ITableModel* table = storageAdapter->loadTableForDataItemType(DataItem::ALBUM);
    int latestID = 0;

    int numberOfAlbums = table->rowCount();
    int numberOfAlbumArtists;
    int albumID;
    Artist* artist;
    QString name;
    Album* newAlbum;
    int albumIDIndex = table->indexOfColumn("id");
    int albumNameIndex = table->indexOfColumn("album");
    QList<int> artistIDs;

    for (int i = 0; i < numberOfAlbums; i++)
    {
        albumID = table->data(table->index(i, albumIDIndex)).toInt();
        if (albumID > latestID)
        {
            latestID = albumID;
        }

        name = table->data(table->index(i, albumNameIndex)).toString();
        newAlbum = new Album(albumID, name, mediaCollection);

        artistIDs = artistToAlbumMap.values(albumID);
        numberOfAlbumArtists = artistIDs.size();
        for (int a = 0; a < numberOfAlbumArtists; a++)
        {
            artist = mediaCollection->getArtistByID(artistIDs.at(a));

            if (artist != 0)
            {
                artist->addAlbum(newAlbum);
                newAlbum->addArtist(artist);
            }
        }

        mediaCollection->insertAlbum(newAlbum);
    }

    mediaCollection->currentAlbumID = latestID;
    delete table;
}

void AudioCollectionBuilder::buildSongs(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
    ITableModel* table = storageAdapter->loadTableForDataItemType(DataItem::SONG);
    int idIndex = table->indexOfColumn("id");
    int nameIndex = table->indexOfColumn("song");
    int yearIndex = table->indexOfColumn("year");
    int artistIdIndex = table->indexOfColumn("artist_id");
    int genreIdIndex = table->indexOfColumn("genre_id");
    int albumIdIndex = table->indexOfColumn("album_id");
    int numberOfSongs = table->rowCount();

    int id;
    int latestID = 0;
    int year;
    int artistID;
    int genreID;
    int albumID;
    QString name;
    Song* song;
    Artist* artist;
    Genre* genre;
    Album* album;

    for (int i = 0; i < numberOfSongs; i++)
    {
        id = table->data(table->index(i, idIndex)).toInt();
        name = table->data(table->index(i, nameIndex)).toString();
        year = table->data(table->index(i, yearIndex)).toInt();
        artistID = table->data(table->index(i,artistIdIndex)).toInt();
        genreID = table->data(table->index(i, genreIdIndex)).toInt();
        albumID = table->data(table->index(i, albumIdIndex)).toInt();

        if (id > latestID)
        {
            latestID = id;
        }

        song = new Song(id, name, year, mediaCollection);

        artist = mediaCollection->getArtistByID(artistID);
        genre = mediaCollection->getGenreByID(genreID);
        album = mediaCollection->getAlbumByID(albumID);

        album->addSong(song);
        song->setAlbum(album);

        song->setGenre(genre);
        genre->addSong(song);

        song->setArtist(artist);

        mediaCollection->insertSong(song);
    }

    mediaCollection->currentSongID = latestID;
    delete table;
}


