#include "AbstractInfoResolver.h"
#include "InfoRequest.h"
#include <QThread>
#include <QApplication>
#include <QDebug>


using namespace Core;
AbstractInfoResolver::AbstractInfoResolver(QObject *parent) :
    IInfoResolver(parent), running(false), workerThread(0)
{
}

InfoRequest *AbstractInfoResolver::getInfoForItem(QString type, Core::DataItem* item)
{
    InfoRequest* request = new InfoRequest(type, item);

    // TODO: mutex for bool running !?!!
    if(running)
    {
        insertInFifo(request);
    }
    else
    {
        if (workerThread == 0)
        {
            qDebug() << "creating new thread";
            workerThread = new QThread(this);
        }

        running = true;
        currentRequest = request;

        connect(workerThread, SIGNAL(started()), this, SLOT(workerThreadStarted()));
        connect(workerThread, SIGNAL(finished()), this, SLOT(threadFinished()));
        this->moveToThread(workerThread);

        workerThread->start();
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
        this->moveToThread(QApplication::instance()->thread());
        workerThread->quit();
    }
}

AbstractInfoResolver::~AbstractInfoResolver()
{
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

void AbstractInfoResolver::threadFinished()
{
    qDebug() << "Thread finished!";
    delete workerThread;
    workerThread = 0;
}

void AbstractInfoResolver::workerThreadStarted()
{
    // start work with current request
    getInfo(currentRequest->getRequestType(), currentRequest->getRelatedItem());
}
