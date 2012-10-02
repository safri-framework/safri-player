#include "artist.h"
#include "album.h"

using namespace Core;

QMap<QString, Artist*> Artist::artistsByName;
QMap<int, Artist*> Artist::artistsByID;
int Artist::latestID = 0;

Artist* Artist::getByName(QString name)
{
    return artistsByName.value(name);
}

Artist* Artist::getByID(int id)
{
    return artistsByID.value(id);
}

QList<Artist *> Artist::getAll()
{
    return artistsByID.values();
}

void Artist::add(Artist* artist)
{
    artistsByName.insert(artist->getName(), artist);
    artistsByID.insert(artist->getID(), artist);
}

void Artist::remove(Artist* artist)
{
    artistsByName.remove(artist->getName());
    artistsByID.remove(artist->getID());
}

int Artist::createNewID()
{
    return ++latestID;
}

Artist::Artist(int sID, QString sName, QObject *parent) :
    BaseDTO(sID, sName, BaseDTO::ARTIST, parent)
{

}

Artist::Artist(int sID, QString sName, bool temporary, QObject *parent):
    BaseDTO(sID, sName, BaseDTO::ARTIST, temporary, parent)
{
}

Artist::Artist(Artist* artist, QObject *parent) :
    BaseDTO(createNewID(), artist->getName(), BaseDTO::ARTIST, parent)
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


