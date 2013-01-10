#include "mediacollectionitemtype.h"

#include "../../CoreData/song.h"
#include "../../Interfaces/IMediaCollection.h"

using namespace Core;

MediaCollectionItemType::MediaCollectionItemType()
{
}

QString MediaCollectionItemType::getTypeName()
{
    return "MediaCollectionType";
}

QString MediaCollectionItemType::getNodeName(Song *song)
{
    return song->getMediaCollection()->getName();
}

DataItem *MediaCollectionItemType::getNodeDataItem(Song *song)
{
    Q_UNUSED(song)
    return 0;
}

QString MediaCollectionItemType::getHash(Song *song)
{
    return song->getMediaCollection()->getName();
}
