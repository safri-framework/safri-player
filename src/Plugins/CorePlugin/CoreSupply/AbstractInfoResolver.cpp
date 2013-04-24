#include "AbstractInfoResolver.h"
#include "InfoRequest.h"


AbstractInfoResolver::AbstractInfoResolver(QObject *parent) :
    IInfoResolver(parent)
{
}

InfoRequest *AbstractInfoResolver::getInfoForItem(QString type, DataItem* item)
{
    InfoRequest* request = new InfoRequest(item);
    if(running)
    {
        insertInFifo(request);
    }
    else
    {
        running = true;
        getInfo(type, item);
        //curr
    }
    return request;

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
