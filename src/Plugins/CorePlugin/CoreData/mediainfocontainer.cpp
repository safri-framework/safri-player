#include "mediainfocontainer.h"

using namespace Core;

MediaInfoContainer::MediaInfoContainer(QUrl mediaUrl, QObject *parent)
    : QObject(parent), mediaUrl(mediaUrl)
{

}

MediaInfoContainer::MediaInfoContainer(MediaInfoContainer &other)
    : QObject( other.parent() ), mediaUrl(other.mediaUrl), infoMap(other.infoMap)
{

}

void MediaInfoContainer::setMediaInfo(MediaInfoType type, QVariant info)
{
    infoMap.insert(type, info);
}

QVariant MediaInfoContainer::getMediaInfo(MediaInfoType type)
{
    if(type == InfoTitle && !infoMap.value(type).isValid())
        return getMediaInfo(InfoURL);
    if(infoMap.value(type).isValid())
        return infoMap.value(type);
    else
        return tr("Unbekannt");
}

QUrl MediaInfoContainer::getURL()
{
    return this->mediaUrl;
}
