#include "AbstractInfoResolver.h"
#include "InfoRequest.h"
#include <QThread>
#include <QApplication>
#include <QDebug>


using namespace Core;
AbstractInfoResolver::AbstractInfoResolver(QObject *parent) :
    IInfoResolver(parent), running(false), workerThread(0), timeOutThreshold(15000)
{
    QMutex fifoMutex();
    timoutTimer = new QTimer(this);
    timoutTimer->setSingleShot(true);
    timoutTimer->setInterval(timeOutThreshold);
    connect(timoutTimer, SIGNAL(timeout()), this, SLOT(timeout()));
}

InfoRequest *AbstractInfoResolver::getInfoForItem(QString type, Core::DataItem* item)
{

    InfoRequest* request = new InfoRequest(type, item);
    // TODO: mutex for bool running !?!!
    if(workerThread && workerThread->isRunning())
    {
        insertInFifo(request);
        qDebug()<<"getInfo" << requestList.size()<<"    "<<item->getName();
    }
    else
    {
        if (workerThread == 0)
        {
            qDebug()<<Q_FUNC_INFO<<" ->creating new thread";
            workerThread = new QThread(this);
        }

        currentRequest = request;
        connect(workerThread, SIGNAL(started()), this, SLOT(workerThreadStarted()));
        connect(workerThread, SIGNAL(finished()), this, SLOT(threadFinished()));
        this->moveToThread(workerThread);
        workerThread->start();
    }

    return request;
}

void AbstractInfoResolver::setError(QString error)
{
    qDebug()<<"ERROR!!!!!!!!!"<< Q_FUNC_INFO << ":" << error;
    timoutTimer->stop();
    currentRequest->setError(error);
    handleNextRequest();
}

void AbstractInfoResolver::setInfo(QVariant info)
{
    qDebug()<< Q_FUNC_INFO ;
    timoutTimer->stop();
    if(currentRequest)
        currentRequest->setInfoData(info);

    currentRequest = 0;
    handleNextRequest();
}

AbstractInfoResolver::~AbstractInfoResolver()
{
}

void AbstractInfoResolver::insertInFifo(InfoRequest *request)
{
    qDebug()<< Q_FUNC_INFO ;
    fifoMutex.lock();
    requestList.append(request);
    fifoMutex.unlock();
}

InfoRequest *AbstractInfoResolver::getNextRequest()
{
    qDebug()<< Q_FUNC_INFO ;
    InfoRequest* nextRequest;
    //fifoMutex.lock();
    nextRequest = requestList.takeFirst();
    //fifoMutex.unlock();
    return nextRequest;
}

bool AbstractInfoResolver::hasRequest()
{
    qDebug()<< Q_FUNC_INFO ;
    bool hasRequest;
    hasRequest = requestList.size() > 0;
    return hasRequest;
}

void AbstractInfoResolver::handleNextRequest()
{
    fifoMutex.lock();
    timoutTimer->stop();
    if(hasRequest())
    {
        currentRequest = getNextRequest();
        getInfo(currentRequest->getRequestType(), currentRequest->getRelatedItem());
        fifoMutex.unlock();
        timoutTimer->start();
        qDebug()<<"handle next:"<<"-> "<< currentRequest->getRelatedItem()->getName()<<requestList.size();
    }
    else
    {
        timoutTimer->stop();
        qDebug()<<Q_FUNC_INFO<<"-> NO REQUESTS";
        this->moveToThread(QApplication::instance()->thread());
        workerThread->exit();
    }
    fifoMutex.unlock();
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
    timoutTimer->start();
}

void AbstractInfoResolver::timeout()
{
    setError("timeOut");
}
