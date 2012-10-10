#include "album.h"
#include "song.h"

using namespace Core;

QMap<QString, Album*> Album::albumsByName;
QMap<int, Album*> Album::albumsByID;
int Album::latestID = 0;

QList<Album*> Album::getByName(QString name)
{
    return albumsByName.values(name);
}

Album* Album::getByID(int id)
{
    return albumsByID.value(id);
}

QList<Album *> Album::getAll()
{
    return albumsByID.values();
}

void Album::add(Album* album)
{
    albumsByName.insert(album->getName(), album);
    albumsByID.insert(album->getID(), album);
}

void Album::remove(Album* album)
{
    albumsByName.remove(album->getName());
    albumsByID.remove(album->getID());
}

int Album::createNewID()
{
    return ++latestID;
}

QList<Media *> Album::getMedia()
{
    //TODO:
    return QList<Media*>();
}

Album::Album(int sID, QString sName, QObject *parent) :
    DataItem(sID, sName, DataItem::ALBUM,  parent)
{

}

Album::Album(Album* album, QObject *parent) :
    DataItem(createNewID(),album->getName(),album->getType(), parent)
{

}

Album::Album(int sID, QString sName, bool temporary, QObject *parent):
DataItem(sID, sName, DataItem::ALBUM, temporary, parent)
{

}

void Album::addArtist(Artist* sArtist)
{
    this->artists.insert(sArtist);
}

QList<Artist*> Album::getArtists()
{
    return this->artists.toList();
}


bool Album::removeArtist(Artist* sArtist)
{
    // first check if there is no more song from the artist
    // in this album

    bool songFromArtist = false;
    int songCount = songs.size();

    for (int i = 0; i < songCount; i++)
    {
        if (songs.at(i)->getArtist() == sArtist)
        {
            songFromArtist = true;
            break;
        }
    }

    // only remove the artist if no more song from it is
    // placed in this album
    if (!songFromArtist)
    {
        this->artists.remove(sArtist);
        return true;
    }

    return false;
}

QList<Song*> Album::getSongs()
{
    return this->songs;
}

void Album::addSong(Song* song)
{
    this->songs.append(song);
}

void Album::removeSong(Song* song)
{
    this->songs.removeOne(song);

    // DO SOME CLEANUP
    int artistCount = artists.size();
    QList<Artist*> artistsToRemove;
    Artist *currentArtist;

    QSetIterator<Artist*> it(artists);

    while (it.hasNext())
    {
        currentArtist = it.next();

        // TODO!!!!
        /*
        if ( DatabaseDAO::getSongCountFromAlbumAndArtist(this, currentArtist) == 0)
        {
            artistsToRemove.append(currentArtist);
        }
        */
    }

    artistCount = artistsToRemove.size();
    for (int i = 0; i < artistCount; i++)
    {
        currentArtist = artistsToRemove.at(i);
        currentArtist->removeAlbum(this);
        this->artists.remove(currentArtist);
    }

}

Album* Album::separateArtist(DataItem *sArtist)
{
    // first find or create an appropriate album object
    Album* newAlbum = 0;
    Artist *artist;

    if (sArtist->getType() != DataItem::ARTIST)
    {
        return 0;
    }

    artist = static_cast<Artist*>(sArtist);
    QList<Album*> albums;

    albums = artist->getAlbumByName(this->name);
    int albumCount = albums.size();
    Album* testAlbum;

    // tests if the artist has already an album, with the appropriate
    // name that is NOT equal to this album
    for (int i = 0; i < albumCount; i++)
    {
        testAlbum = albums.at(i);
        if (testAlbum != this)
        {
            newAlbum = testAlbum;
            break;
        }
    }

    if (newAlbum == 0)
    {
        // create a new album object with a new id, the name of this
        // album and the QObject parent of this album
        newAlbum = new Album(this, this->parent());

        // add the artist to the new album
        newAlbum->addArtist(artist);
    }

    // now iterate through all songs and move songs from the artist
    // to the new album
    int songCount = songs.size();
    QList<Song*> songsToMove;
    Song *song;

    for (int i = 0; i < songCount; i++)
    {
        song = songs.at(i);
        if (song->getArtist() == artist)
        {
            songsToMove.append(song);
        }
    }

    songCount = songsToMove.size();
    for (int i = 0; i < songCount; i++)
    {
        songsToMove.at(i)->moveToAlbum(newAlbum);
    }

    return newAlbum;
}

bool Album::isCompilation()
{
    return (artists.size() > 1);
}

QString Album::getCoverFile()
{
    return albumCoverFile;
}

void Album::setCoverFile(QString sCoverFile)
{
    albumCoverFile = sCoverFile;
}
