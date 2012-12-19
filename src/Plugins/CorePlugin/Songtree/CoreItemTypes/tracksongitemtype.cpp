#include "tracksongitemtype.h"

#include <QString>

#include "song.h"

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

QList<QAction *> *TrackSongItemType::getContextMenuActions(SongTreeItem *item)
{
    return 0;
}
