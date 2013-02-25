#include "artist.h"
#include "album.h"

using namespace Core;


QList<Media *> Artist::getMedia()
{
    //TODO
    return QList<Media*>();
}

Artist::Artist(int sID, QString sName, QObject *parent) :
    DataItem(sID, sName, DataItem::ARTIST, parent)
{

}

Artist::Artist(int sID, QString sName, bool temporary, QObject *parent):
    DataItem(sID, sName, DataItem::ARTIST, temporary, parent)
{
}

Artist::Artist(Artist* artist, QObject *parent) :
    DataItem(-1 /* TODO */, artist->getName(), DataItem::ARTIST, parent)
{

}

QList<Album*>& Artist::getAlbums()
{
    return this->albums;
}

void Artist::addAlbum(Album* album)
{
    if (!this->albums.contains(album))
        this->albums.append(album);
}

void Artist::removeAlbum(Album* album)
{
    this->albums.removeOne(album);
}

QList<Album*> Artist::getAlbumByName(QString name)
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


