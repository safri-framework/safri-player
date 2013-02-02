#include "mediainfocontainer.h"

using namespace Core;

MediaInfoContainer::MediaInfoContainer(QUrl mediaUrl, QObject *parent)
    : QObject(parent), mediaUrl(mediaUrl)
{
}

void MediaInfoContainer::setMediaInfo(MediaInfoType type, QString info)
{
    infoMap.insert(type, info);
}

QString MediaInfoContainer::getMediaInfo(MediaInfoType type)
{
    return infoMap.value(type);
}
