#include "song.h"
using namespace Core;


QList<Media *> Song::getMedia()
{
    QList<Media*> myMedia;
    myMedia.append(this);

    return myMedia;
}

QUrl Song::getURL()
{
    return QUrl(filename);
}

QString Song::getMimeType()
{
    // TODO: read MimeType from database
    return "audio/mpeg";
}

Song::Song(int sID, QString sName, int year, QString filename, QObject *parent) :
    Media(sID, sName, DataItem::SONG, parent), filename(filename), year(year)
{

}

Song::Song(int sID, QString sName, int year,  QObject *parent) :
    Media(sID, sName, DataItem::SONG, parent), year(year)
{

}

Song::Song(int sID, QString sName, int year,  QString filename, bool temporary, QObject *parent):
    Media(sID, sName, DataItem::SONG, temporary, parent), filename(filename), year(year)
{

}

Artist* Song::getArtist()
{
    return this->interpret;
}

Album* Song::getAlbum()
{
    return this->album;
}

Genre* Song::getGenre()
{
    return this->genre;
}

void Song::setArtist(Artist* sArtist)
{
    this->interpret = sArtist;
}

void Song::setAlbum(Album* sAlbum)
{
    this->album = sAlbum;
}

void Song::setGenre(Genre* sGenre)
{
    this->genre = sGenre;
}

int Song::getYear()
{
   return year;
}

QString Song::getFileName()
{
    return filename;
}

int Song::getTrack()
{
    return track;
}

int Song::getLength()
{
    return length;
}

void Song::setTrack(int track)
{
    this->track = track;
}

void Song::setLength(int length)
{
    this->length = length;
}

bool Song::moveToArtist(DataItem *newArtist)
{
    Artist *artist, *oldArtist;

    if (newArtist->getType() != DataItem::ARTIST)
    {
        return false;
    }

    artist = static_cast<Artist*>(newArtist);

    oldArtist = this->interpret;

    // change the artist of this song
    this->interpret = artist;

    if ( this->album->removeArtist(oldArtist) )
    {
        oldArtist->removeAlbum(this->album);
    }

    // and add the album of this song, to the new artist
    artist->addAlbum(this->album);

    // and also add the artist to this album
    this->album->addArtist(artist);

    return true;
}

bool Song::moveToAlbum(DataItem *newAlbum)
{
    Album *album;

    if (newAlbum->getType() != DataItem::ALBUM)
    {
        return false;
    }

    album = static_cast<Album*>(newAlbum);

    // remove the song from the old Album
    this->album->removeSong(this);

    // remove the artist from the album (if there is no more song from it)
    if ( this->album->removeArtist(this->interpret) )
    {
        this->interpret->removeAlbum(this->album);
    }

    this->album = album;

    // add the artist to the new album
    album->addArtist(this->interpret);

    // add the album to the artist
    this->interpret->addAlbum(album);

    // add this song to the new album
    album->addSong(this);

    return true;
}

bool Song::moveToGenre(DataItem *newGenre)
{
    Genre* genre;

    if (newGenre->getType() != DataItem::GENRE)
    {
        return false;
    }

    genre = static_cast<Genre*>(newGenre);

    this->genre->removeSong(this);
    genre->addSong(this);

    this->genre = genre;

    return true;
}
