#include "artistsongitemtype.h"
#include <QString>
#include "../../CoreData/song.h"

using namespace Core;

ArtistSongItemType::ArtistSongItemType()
{
}

QString ArtistSongItemType::getTypeName()
{
    return "ArtistSongType";
}

QString ArtistSongItemType::getNodeName(Song* song)
{
    return song->getArtist()->getName() + " - " + song->getName();
}

DataItem* ArtistSongItemType::getNodeDataItem(Song *song)
{
    return song;
}

QString ArtistSongItemType::getHash(Song *song)
{
    return QString::number(song->getID()) + song->getName();
}
