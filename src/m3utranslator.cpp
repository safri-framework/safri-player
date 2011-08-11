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

TreeItem* M3uTranslator::getPlaylistTree()
{
    TreeItem* root = new TreeItem(0,"ROOT",0,"root",0);

    QDir directory(DirName);

    QStringList filters;

    filters << "*.m3u";

    directory.setNameFilters(filters);

    QDirIterator lukeFileWalker(directory);


        while (lukeFileWalker.hasNext())
        {
            lukeFileWalker.next();
            QFileInfo info = lukeFileWalker.fileInfo();

            QString plName = info.fileName().replace(QRegExp(".m3u"),"");

            Playlist* pl = new Playlist(info.absoluteFilePath());
            TreeItem* child = new TreeItem(pl,"PLAYLIST",info.absoluteFilePath(),plName, root);



            for (int i = 0; i <pl->getSongCount(); i++ )
            {

                AudioFile* af = pl->getAudioFileAt(i);

                //af->ReadTags();
                QFileInfo songinfo(af->fileName());
                QString text = songinfo.fileName();
                TreeItem* childItem = new TreeItem(0,"SONG", af->fileName(),text,child);
                child->getChilds()->append(childItem);
            }
            root->getChilds()->append(child);
        }

return root;

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


