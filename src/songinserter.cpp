#include "songinserter.h"


SongInserter::SongInserter(QStringList *sFileList, QObject *parent) :
    QThread(parent), fileList(sFileList)
{
}


void SongInserter::run()
{
    DatabaseDAO::loadAlbumCoverFilePatterns();

    QTime timer;

    qDebug() << "Starting timer...";
    timer.start();

    for (int i = 0; i < fileList->size(); i++)
    {
        AudioFile song(fileList->at(i));
        song.ReadTags();
        DatabaseDAO::insertSongWithCover(song);
        Q_EMIT songInserted(i);

    }

    qDebug() << "Duration of inserting (with cover): " << ((float) timer.elapsed() / 1000.f);

}
