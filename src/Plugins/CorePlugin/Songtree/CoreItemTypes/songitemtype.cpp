#include "songitemtype.h"

using namespace Core;

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


DataItem* SongItemType::getNodeDataItem(Song *song)
{
    return song;
}

QString SongItemType::getHash(Song *song)
{
    return QString::number(song->getID()) + song->getName();
}

