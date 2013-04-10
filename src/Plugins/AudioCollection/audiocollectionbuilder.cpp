#include "audiocollectionbuilder.h"
#include <CoreData/dataitemtablemodel.h>
#include <QList>
#include <QDebug>

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
        name = "Safri Musik Sammlung";
    }
    else
    {

    }

    AudioCollection* audioCollection = new AudioCollection(name);

    storageAdapter->beginRead();

        buildGenres(storageAdapter, audioCollection);
        buildArtists(storageAdapter, audioCollection);
        buildAlbums(storageAdapter, audioCollection);
        buildSongs(storageAdapter, audioCollection);

    storageAdapter->endRead();

    /*
    storageAdapter->beginWrite();

        Core::ITableModel* model;

        model = buildGenreTable(audioCollection);
        storageAdapter->writeTableForDataItemType(model, Core::DataItem::GENRE);
        delete model;

        model = buildArtistTable(audioCollection);
        storageAdapter->writeTableForDataItemType(model, Core::DataItem::ARTIST);
        delete model;

    storageAdapter->endWrite();
    */

    return audioCollection;
}

void AudioCollectionBuilder::storeMediaCollection(IMediaCollection *mediaCollection, IStorageAdapter *storageAdapter)
{
    Q_UNUSED(mediaCollection)
    Q_UNUSED(storageAdapter)
}

QString AudioCollectionBuilder::getCollectionType()
{
    return "org.safri.collection.audio";
}

void AudioCollectionBuilder::fillMetaInfo(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
    mediaCollection->m_databaseLocation = storageAdapter->getStoragePath();
}

void AudioCollectionBuilder::buildGenres(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
    ITableModel* table = storageAdapter->loadTableForDataItemType(DataItem::GENRE);

    if (table == 0)
    {
        return;
    }

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

    if (table == 0)
    {
        return;
    }

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

    if (table == 0)
    {
        return QMultiMap<int, int>();
    }

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

    if (table == 0)
    {
        return;
    }

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

    if (table == 0)
    {
        return;
    }

    int idIndex = table->indexOfColumn("id");
    int nameIndex = table->indexOfColumn("song");
    int yearIndex = table->indexOfColumn("year");
    int filenameIndex = table->indexOfColumn("filename");
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
    QString filename;
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
        filename = table->data(table->index(i, filenameIndex)).toString();
        if (id > latestID)
        {
            latestID = id;
        }

        song = new Song(id, name, year, filename, mediaCollection);


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

ITableModel *AudioCollectionBuilder::buildGenreTable(AudioCollection *mediaCollection)
{
    QList<Core::Genre*> genres = mediaCollection->getGenres();
    int genreCount = genres.size();
    Core::DataItemTableModel* tableModel = new Core::DataItemTableModel(genreCount, 2);

    tableModel->setHeaderData(0, Qt::Horizontal, "id");
    tableModel->setHeaderData(1, Qt::Horizontal, "genre");

    Core::Genre* genre;

    for (int i = 0; i < genreCount; i++)
    {
        genre = genres.at(i);
        tableModel->setData(tableModel->index(i, 0), genre->getID());
        tableModel->setData(tableModel->index(i, 1), genre->getName());
    }

    return tableModel;
}

ITableModel *AudioCollectionBuilder::buildArtistTable(AudioCollection *mediaCollection)
{
    QList<Core::Artist*> artists = mediaCollection->getArtists();
    int artistCount = artists.size();
    Core::DataItemTableModel* tableModel = new Core::DataItemTableModel(artistCount - 1, 2); // subtract the "unknown" artist

    tableModel->setHeaderData(0, Qt::Horizontal, "id");
    tableModel->setHeaderData(1, Qt::Horizontal, "artist");

    Core::Artist* artist;
    int tableRow = 0;

    for (int i = 0; i < artistCount; i++)
    {
        artist = artists.at(i);

        if (artist->getID() == -1)
        {
            // ommit default artist "unknown"
            continue;
        }

        if (artist->getID() < 100)
            qDebug() << artist->getID() << " : " << artist->getName() << " : " << tableRow;

        tableModel->setData(tableModel->index(tableRow, 0), artist->getID());
        tableModel->setData(tableModel->index(tableRow, 1), artist->getName());
        tableRow++;
    }

    return tableModel;
}


