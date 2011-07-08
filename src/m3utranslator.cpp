#include "m3utranslator.h"

const QString M3uTranslator::DirName= "playlists";

Playlist* M3uTranslator::getPlaylistFromM3u(QString absoluteFilename)
{
    QList<AudioFile*> *list = new QList<AudioFile*>();

    QFile m3u( absoluteFilename );

    m3u.open(QIODevice::ReadOnly);
    QTextStream fileStream(&m3u);
    while (!fileStream.atEnd())
    {
        QString path = fileStream.readLine();
        if (path.at(0)!='#') list->append(new AudioFile(path));
    }

    Playlist* playlist = new Playlist(list);
   return playlist;

}


QStringList M3uTranslator::getPlaylists()
{
    QDir directory(DirName);
    QStringList m3uFiles;

    QStringList filters;

    filters << "*.m3u";

    directory.setNameFilters(filters);

    QDirIterator lukeFileWalker(directory);


    while (lukeFileWalker.hasNext())
    {
        lukeFileWalker.next();
        m3uFiles.append( lukeFileWalker.fileInfo().fileName().replace(QRegExp(".m3u"),"") );
    }
return m3uFiles;

}


void M3uTranslator::savePlaylistToM3u(Playlist* playlist, QString absoluteFilename)
{
    QFile file( absoluteFilename );


    // QFile file( directory.absoluteFilePath(filename) ); Nur als gedächtsnisstütze


    if (!file.open(QFile::WriteOnly))
    {

        qDebug() << "Datei konnte nich geöffnet werden!  " << file.errorString();
             return;
    }

    QTextStream fileStream(&file);

    for (int i=0; i<playlist->getSongCount(); i++)
    {
        fileStream << playlist->getAudioFileAt(i)->fileName() << endl;
    }

    file.close();
}

QString M3uTranslator::playlistNameToAbsPath(QString playlistname)
{
    QDir directory(DirName);

    return directory.absoluteFilePath(playlistname + ".m3u");
}
