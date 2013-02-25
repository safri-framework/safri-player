#include "filesysteminserter.h"
#include <QDebug>
#include <QThread>
#include "../icore.h"
#include "../Interfaces/IMediaTagger.h"
#include "../Interfaces/IMediaCollection.h"
#include "../Interfaces/ICollectionController.h"
#include "pluginmanager.h"
#include <QList>
#include <QDirIterator>
#include <QApplication>

using namespace Core;

FileSystemInserter::FileSystemInserter(IMediaCollection *collection) :
    IMediaInserter(), collection(collection), mediaUrlToInsert(QUrl()), taggerForInsert(0), numberOfFiles(0), currentFile(0)
{

}

FileSystemInserter::~FileSystemInserter()
{
    qDebug() << "~FileSystemInserter()";
}

void FileSystemInserter::start()
{
    Q_EMIT mediaInsertionStarted(collection);

    QFileInfo fileInfo(mediaUrlToInsert.toString());

    if (fileInfo.isDir())
    {
        QDir directory = mediaUrlToInsert.toString();

        QStringList filters;

        filters.append("*.mp3");
        directory.setNameFilters(filters);

        QDirIterator iterator(directory, QDirIterator::Subdirectories);
        QStringList files;

        // first, collect all file paths
        while (iterator.hasNext())
        {
            iterator.next();
            QString path = iterator.fileInfo().absoluteFilePath();
            files.append(path);
        }

        numberOfFiles = files.size();
        connect(taggerForInsert, SIGNAL(mediaTagged(MediaInfoContainer)), this, SLOT(mediaTagged(MediaInfoContainer)));

        for (currentFile = 0; currentFile < numberOfFiles; currentFile++)
        {
            taggerForInsert->tagMedia(QUrl(files.at(currentFile)));
        }

        disconnect(taggerForInsert, SIGNAL(mediaTagged(MediaInfoContainer)), this, SLOT(mediaTagged(MediaInfoContainer)));
    }

    collection->moveToThread(QApplication::instance()->thread());
    taggerForInsert->moveToThread(QApplication::instance()->thread());
    this->moveToThread(QApplication::instance()->thread());

    emit finished();
}

void FileSystemInserter::mediaTagged(MediaInfoContainer info)
{
    //qDebug() << "media Tagged: " << info.getMediaInfo(InfoArtist);
    collection->addMedia(info);
}

void FileSystemInserter::insertMedia(QUrl mediaUrl, IMediaTagger *tagger)
{
    mediaUrlToInsert = mediaUrl;
    taggerForInsert = tagger;

    thread = new QThread;

    collection->moveToThread(thread);
    tagger->moveToThread(thread);
    this->moveToThread(thread);

    connect(thread, SIGNAL(started()), this, SLOT(start()));
    connect(thread, SIGNAL(finished()), thread, SLOT(quit()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(this, SIGNAL(finished()), this, SLOT(threadFinished()));

    qDebug() << "Starte neuen Thread";
    thread->start();
}

void FileSystemInserter::threadFinished()
{
    qDebug() << "ENDE UND AUS";
    Q_EMIT mediaInsertionFinished(collection);
    deleteLater();
}

