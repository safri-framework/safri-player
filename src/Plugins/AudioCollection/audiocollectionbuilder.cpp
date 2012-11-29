#include "audiocollectionbuilder.h"
#include <Interfaces/ITableModel.h>


AudioCollectionBuilder::AudioCollectionBuilder(QObject *parent) :
    QObject(parent)
{
}

IMediaCollection *AudioCollectionBuilder::buildMediaCollection(IStorageAdapter *storageAdapter, MetaInfoAdaper* adapter)
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

    currentAudioCollection = new AudioCollection(name);





}

void AudioCollectionBuilder::storeMediaCollection(IMediaCollection *mediaCollection, IStorageAdapter *storageAdapter)
{

}

void AudioCollectionBuilder::buildGenres(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
    ITableModel* table = storageAdapter->loadTableForDataItemType(DataItem::GENRE);
    int idIndex = table->indexOfColumn("ID");
    int nameIndex = table->indexOfColumn("GENRE");



    for (int i = 0; i < table->rowCount(); i++)
    {
        int id = table->index(i, idIndex);
        QString name = table->index(i, nameIndex);
        mediaCollection->insertGenre(new Genre(id, name, mediaCollection));
    }

}

void AudioCollectionBuilder::buildArtists(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
    ITableModel* table = storageAdapter->loadTableForDataItemType(DataItem::ARTIST);
    int idIndex = table->indexOfColumn("ID");
    int nameIndex = table->indexOfColumn("ARTIST");





    for (int i = 0; i < table->rowCount(); i++)
    {
        int id = table->index(i, idIndex);
        QString name = table->index(i, nameIndex);
        mediaCollection->insertArtist(new Artist(id, name, mediaCollection));
    }
}

void AudioCollectionBuilder::buildAlbums(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{


}

void AudioCollectionBuilder::buildSongs(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
     ITableModel* table = storageAdapter->loadTableForDataItemType(DataItem::SONG);
     int idIndex = table->indexOfColumn("ID");
     int nameIndex = table->indexOfColumn("NAME");
    int yearIndex = table->indexOfColumn("year");
    int artistIdIndex = table->indexOfColumn("artist_id"); ;
    int genreIdIndex = table->indexOfColumn("genre_id"); ;
    int albumIdIndex = table->indexOfColumn("album_id"); ;




    for (int i = 0; i < table->rowCount(); i++)
    {
        int id = table->index(i, idIndex);
        QString name = table->index(i, nameIndex);
        int year = table->index(i, yearIndex);
        int artistID = table->index(i,artistIdIndex);
        int genreID = table->index(i, genreIdIndex);
        int albumID = table->index(i, albumIdIndex);

        Song* song = new Song(id, name, year, mediaCollection);

        Artist* artist = mediaCollection->getArtistByID(artistID);
        Genre* genre = mediaCollection->getGenreByID(genreID);
        Album* album = mediaCollection->getAlbumByID(albumID);

        album->addSong(song);
        song->setAlbum(album);

        song->setGenre(genre);
        genre->addSong(song);

        song->setArtist(artist);




        mediaCollection->insertSong();
    }

}
