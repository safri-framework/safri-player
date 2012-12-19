#include "tracksongitemtype.h"
#include <QString>
#include "../../CoreData/song.h"

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

BaseDTO* TrackSongItemType::getNodeDTO(Song *song)
{
    return song;
}

QString TrackSongItemType::getHash(Song *song)
{
    return QString::number(song->getID()) + song->getName();
}

