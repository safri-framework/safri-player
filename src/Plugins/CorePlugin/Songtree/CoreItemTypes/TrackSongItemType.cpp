#include "TrackSongItemType.h"
#include <QString>
#include "../../CoreData/Song.h"

using namespace Core;

TrackSongItemType::TrackSongItemType()
{
}

QString TrackSongItemType::getTypeName()
{
    return "TrackSongType";
}

QString TrackSongItemType::getNodeName(Song* song)
{
    return ((song->getTrack() < 10) ? "0" : "") + QString::number(song->getTrack()) + ". " + song->getName();
}

DataItem* TrackSongItemType::getNodeDataItem(Song *song)
{
    return song;
}

QString TrackSongItemType::getHash(Song *song)
{
    return QString::number(song->getID()) + song->getName();
}

