#include "albumitemtype.h"
#include "../../CoreData/song.h"
#include "../../CoreData/album.h"


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


BaseDTO* AlbumItemType::getNodeDTO(Song *song)
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


