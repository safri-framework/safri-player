#include "artistitemtype.h"
#include "../../CoreData/song.h"

using namespace Core;

ArtistItemType::ArtistItemType()
{


}


QString ArtistItemType::getTypeName()
{
    return "ArtistType";
}


QString ArtistItemType::getNodeName(Song* song)
{
    return song->getArtist()->getName();
}


DataItem* ArtistItemType::getNodeDataItem(Song *song)
{
    return song->getArtist();
}


QString ArtistItemType::getHash(Song *song)
{
    Artist *artist = song->getArtist();
    return QString::number(artist->getID()) + artist->getName();
}


