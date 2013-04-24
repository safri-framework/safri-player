#include "InfoRequest.h"

InfoRequest::InfoRequest(QObject *parent) :
    QObject(parent)
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

QVariant InfoRequest::getInfo()
{
    return info;
}
