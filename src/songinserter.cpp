#include "songinserter.h"
#include "databasedao.h"


SongInserter::SongInserter(QStringList *sFileList, QObject *parent) :
    QThread(parent), fileList(sFileList)
{
}


void SongInserter::run()
{
    DatabaseDAO::refreshAlbumCoverFilePatterns();

    QTime timer;

    qDebug() << "Starting timer...";
    timer.start();



    for (int i = 0; i < fileList->size(); i++)
    {
        QString path = fileList->at(i);
        QString test = QString::fromStdString(path.toStdString());






        if(!(test.contains("?")))
        {
            qDebug()<<test;
            AudioFile song(test);
            song.ReadTags();
            DatabaseDAO::insertSongWithCover(song);
            Q_EMIT songInserted(i);
            qDebug()<<path;

        }



    }

    qDebug() << "Duration of inserting (with cover): " << ((float) timer.elapsed() / 1000.f);
    DatabaseDAO::loadDataTable();
}
