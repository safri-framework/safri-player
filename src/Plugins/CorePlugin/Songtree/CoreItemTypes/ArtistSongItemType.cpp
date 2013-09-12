#include "ArtistSongItemType.h"
#include <QString>
#include "../../CoreData/Song.h"

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
