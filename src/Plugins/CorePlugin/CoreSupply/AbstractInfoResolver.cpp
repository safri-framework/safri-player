#include "AbstractInfoResolver.h"
#include "InfoRequest.h"


AbstractInfoResolver::AbstractInfoResolver(QObject *parent) :
    IInfoResolver(parent)
{
}

InfoRequest *AbstractInfoResolver::getInfoForItem(QString type, Item *DataItem)
{
    InfoRequest* request = new InfoRequest(DataItem);

}

void AbstractInfoResolver::insertInFifo(InfoRequest *request)
{
    fifoMutex.lock();
    requestList.append(request);
    fifoMutex.unlock();
}


InfoRequest *AbstractInfoResolver::getNextRequest()
{
    InfoRequest* nextRequest;
    fifoMutex.lock();
    nextRequest = requestList.takeFirst();
    fifoMutex.unlock();
    return nextRequest;
}

bool AbstractInfoResolver::hasRequest()
{
    bool hasRequest;

}
