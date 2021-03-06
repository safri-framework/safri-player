#include "AlbumItemType.h"
#include "CoreData/Song.h"
#include "CoreData/Album.h"


using namespace Core;

AlbumItemType::AlbumItemType()
{
}


QString AlbumItemType::getTypeName()
{
    return "AlbumType";
}


QString AlbumItemType::getNodeName(Song* song)
{

return song->getAlbum()->getName();

}


DataItem* AlbumItemType::getNodeDataItem(Song *song)
{
    return song->getAlbum();

}

QString AlbumItemType::getHash(Song *song)
{
    Album*  album = song->getAlbum();
    int id;

    if (album->getName() == "Unbekannt")
    {
        id = 0;
    }
    else
    {
        id = album->getID();
    }

    return QString::number(id) + album->getName();
}


