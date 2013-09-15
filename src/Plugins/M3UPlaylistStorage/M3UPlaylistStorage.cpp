#include "M3UPlaylistStorage.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "Interfaces/ICore.h"
#include "CoreData/Media.h"

M3UPlaylistStorage::M3UPlaylistStorage(QObject *parent) :
    IPlaylistStorage(parent)
{
}

QString M3UPlaylistStorage::getDescription()
{
    return "M3U Playlist";
}

QString M3UPlaylistStorage::getFileExtension()
{
    return "m3u";
}

QSharedPointer<Core::IPlaylist> M3UPlaylistStorage::loadPlaylist(QString filename)
{
    return Core::ICore::createPlaylist();
}

bool M3UPlaylistStorage::savePlaylist(QString filename, QSharedPointer<Core::IPlaylist> playlist)
{
    //qDebug() << "saving playlist as m3u to: " << filename;
    //qDebug() << "playlist len: " << playlist->getSize();

    Core::Media* media;
    QFile m3uFile(filename);

    if ( !m3uFile.open(QFile::WriteOnly) )
    {
        qDebug() << "Failed open file: " << filename;
        return false;
    }

    QTextStream fileStream(&m3uFile);

    for (int i = 0; i < playlist->getSize(); i++)
    {
        media = playlist->getMediaAt(i);
        //qDebug() << "saving: " << media->getURL().toLocalFile();
        fileStream << media->getURL().toLocalFile() << endl;
    }

    m3uFile.close();

    return true;
}
