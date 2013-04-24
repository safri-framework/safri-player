#include "AbstractInfoResolver.h"
#include "InfoRequest.h"


AbstractInfoResolver::AbstractInfoResolver(QObject *parent) :
    IInfoResolver(parent), running(false)
{
}

InfoRequest *AbstractInfoResolver::getInfoForItem(QString type, DataItem* item)
{
    InfoRequest* request = new InfoRequest(type, item);
    if(running)
    {
        insertInFifo(request);
    }
    else
    {
        running = true;
        currentRequest = request;
        getInfo(type, item);
    }
    return request;
}

void AbstractInfoResolver::setInfo(QVariant info)
{
    currentRequest->setInfoData(info);
    currentRequest = 0;
    if(hasRequest())
    {
        currentRequest = getNextRequest();
        getInfo(currentRequest->getRequestType(), currentRequest->getRelatedItem());
    }
    else
    {
        running  = false;
    }
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
    fifoMutex.lock();
    hasRequest = requestList.size() > 0;
    fifoMutex.unlock();
    return hasRequest;
}
