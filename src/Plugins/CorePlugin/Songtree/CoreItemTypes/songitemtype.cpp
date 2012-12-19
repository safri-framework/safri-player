#include "songitemtype.h"

SongItemType::SongItemType()
{

}


QString SongItemType::getTypeName()
{
    return "SongType";
}

QString SongItemType::getNodeName(Song* song)
{
    return song->getName();
}


BaseDTO* SongItemType::getNodeDTO(Song *song)
{
    return song;
}

QString SongItemType::getHash(Song *song)
{
    return QString::number(song->getID()) + song->getName();
}

QList<QAction *> *SongItemType::getContextMenuActions(SongTreeItem *item)
{
    return 0;
}
