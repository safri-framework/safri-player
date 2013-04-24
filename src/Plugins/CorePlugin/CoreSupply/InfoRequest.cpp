#include "InfoRequest.h"

InfoRequest::InfoRequest(Item* relatedItem, QObject *parent) :
    QObject(parent),
    relatedItem(relatedItem)
{
}

void InfoRequest::setInfoData(QVariant info)
{
    this->info = info;
    infoAvailable = true;
    Q_EMIT infoDataAvailable();
}

bool InfoRequest::isInfoAvailable()
{
    return infoAvailable;
}

Item *InfoRequest::getRelatedItem()
{
    return relatedItem;
}

QVariant InfoRequest::getInfo()
{
    return info;
}
