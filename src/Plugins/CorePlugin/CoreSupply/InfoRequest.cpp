#include "InfoRequest.h"

using namespace Core;

InfoRequest::InfoRequest(QString requestType, DataItem* relatedItem, QObject *parent) :
    QObject(parent),
    relatedItem(relatedItem),
    requestType(requestType)
{
}

void InfoRequest::setInfoData(QVariant info)
{
    this->info = info;
    infoAvailable = true;
    Q_EMIT infoDataAvailable();
}

void InfoRequest::setError(QString errorString)
{
    infoAvailable = false;
    errorString = errorString;
    this->info = QVariant();
    Q_EMIT error();
    Q_EMIT infoDataAvailable();
}

bool InfoRequest::isInfoAvailable()
{
    return infoAvailable;
}

DataItem *InfoRequest::getRelatedItem()
{
    return relatedItem;
}

QVariant InfoRequest::getInfo()
{
    return info;
}

QString InfoRequest::getRequestType()
{
    return requestType;
}

QString InfoRequest::getErrorString()
{
    return errorString;
}
