#include "mediainfocontainer.h"

using namespace Core;

MediaInfoContainer::MediaInfoContainer(QUrl mediaUrl)
    : mediaUrl(mediaUrl)
{

}

void MediaInfoContainer::setMediaInfo(MediaInfoType type, QVariant info)
{
    infoMap.insert(type, info);
}

QVariant MediaInfoContainer::getMediaInfo(MediaInfoType type)
{
    return infoMap.value(type);
}
