#include "filesysteminserterworker.h"

#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include <QApplication>
#include <QDebug>

#include "../Interfaces/IMediaCollection.h"
#include "../Interfaces/IMediaTagger.h"

using namespace Core;

FileSystemInserterWorker::FileSystemInserterWorker(IMediaCollection *collection, QUrl mediaUrl, IMediaTagger *tagger) :
    QObject(), collection(collection), mediaUrlToInsert(mediaUrl), taggerForInsert(tagger)
{
}

FileSystemInserterWorker::~FileSystemInserterWorker()
{
    qDebug() << "FileSystemInserterWorker destroyed";
}

void FileSystemInserterWorker::process()
{
    Q_EMIT error("FileSystemInserterWorker::process() called");
    qDebug() << "FileSystemInserterWorker::process() called";

    //Q_EMIT mediaInsertionStarted(collection);

    QFileInfo fileInfo(mediaUrlToInsert.toLocalFile());

    if (fileInfo.isDir())
    {
        QDir directory = fileInfo.absoluteDir();
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
            //qDebug() << "Found file " << path;

            files.append(path);
        }

        numberOfFiles = files.size();
        connect(taggerForInsert, SIGNAL(mediaTagged(MediaInfoContainer)), this, SLOT(mediaTagged(MediaInfoContainer)));

        for (currentFile = 0; currentFile < numberOfFiles; currentFile++)
        {
            taggerForInsert->tagMedia(QUrl(files.at(currentFile)));
            QApplication::processEvents();
        }

        disconnect(taggerForInsert, SIGNAL(mediaTagged(MediaInfoContainer)), this, SLOT(mediaTagged(MediaInfoContainer)));
    }

    Q_EMIT error("wusel dusel");
    Q_EMIT mediaInsertionFinished();

    //collection->moveToThread(QApplication::instance()->thread());

    Q_EMIT finished();
}

void FileSystemInserterWorker::mediaTagged(MediaInfoContainer info)
{
    //qDebug() << "mediaTagged" << info.getMediaInfo(InfoGenre);
    collection->addMedia(info);
}
