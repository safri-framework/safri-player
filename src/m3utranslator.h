#ifndef M3UTRANSLATOR_H
#define M3UTRANSLATOR_H
#include "playlist.h"
#include <QFile>
#include <QDir>
#include <QStringList>

#include <QDirIterator>
#include <QMessageBox>
#include <QUrl>
#include <basedto.h>
#include <treeitem.h>
class M3uTranslator
{
public:

    M3uTranslator();
    static Playlist* getPlaylistFromM3u(QString absoluteFilename);
    static QStringList getPlaylists();
    static void savePlaylistToM3u(Playlist* playlist, QString absoluteFilename);
    static TreeItem* getPlaylistTree();
    static QString playlistNameToAbsPath(QString playlistname);
    //static void addSongToPlaylist(QString playlistPath);
    static const QString DirName;
    static bool deletePlaylist(QString playlistname);

private:


};

#endif // M3UTRANSLATOR_H
