#include "AlbumArtist.h"
#include "Album.h"

using namespace Core;


QList<Media *> AlbumArtist::getMedia()
{
    //TODO
    return QList<Media*>();
}

AlbumArtist::AlbumArtist(int sID, QString sName, QObject *parent) :
    DataItem(sID, sName, DataItem::ALBUMARTIST, parent)
{

}

AlbumArtist::AlbumArtist(int sID, QString sName, bool temporary, QObject *parent):
    DataItem(sID, sName, DataItem::ALBUMARTIST, temporary, parent)
{
}

AlbumArtist::AlbumArtist(AlbumArtist* artist, QObject *parent) :
    DataItem(-1 /* TODO */, artist->getName(), DataItem::ALBUMARTIST, parent)
{

}

QList<Album*>& AlbumArtist::getAlbums()
{
    return this->albums;
}

void AlbumArtist::addAlbum(Album* album)
{
    if (!this->albums.contains(album))
        this->albums.append(album);
}

void AlbumArtist::removeAlbum(Album* album)
{
    this->albums.removeOne(album);
}

QList<Album*> AlbumArtist::getAlbumByName(QString name)
{
    QList<Album*> albumsByName;
    int albumCount = albums.size();
    Album* album;

    for (int i = 0; i < albumCount; i++)
    {
        album = albums.at(i);
        if (album->getName() == name)
        {
            albumsByName.append(album);
        }
    }

    return albumsByName;
}


