#include "filesysteminserter.h"
#include "../Interfaces/IMediaCollection.h"
#include "../Interfaces/IMediaTagger.h"

#include <QThread>
#include "filesysteminserterworker.h"

#include <QDebug>
#include <QApplication>

using namespace Core;

FileSystemInserter::FileSystemInserter(IMediaCollection *collection) :
    IMediaInserter(), collection(collection)
{
}

void FileSystemInserter::insertMedia(QUrl mediaUrl, IMediaTagger *tagger)
{
    qDebug() << "FileSystemInserter::insertMedia()";

    FileSystemInserterWorker *worker = new FileSystemInserterWorker(collection, mediaUrl, tagger);
    tagger->setParent(worker);

    QThread* thread = new QThread();

    //collection->moveToThread(thread);



    worker->moveToThread(thread);

    connect(worker, SIGNAL(error(QString)), this, SLOT(errorMessage(QString)), Qt::QueuedConnection);
    connect(thread, SIGNAL(started()), worker, SLOT(process()));

    connect(worker, SIGNAL(mediaInsertionFinished()), this, SLOT(mediaInsertionFinished()), Qt::QueuedConnection);

    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));

    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    qDebug() << "start Thread";
    thread->start();

}

void FileSystemInserter::errorMessage(QString error)
{
    qDebug() << error;
}

void FileSystemInserter::mediaInsertionFinished()
{
    qDebug() << "FileSystemInserter::workerFinished()";
}


