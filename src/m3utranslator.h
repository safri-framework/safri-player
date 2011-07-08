#ifndef M3UTRANSLATOR_H
#define M3UTRANSLATOR_H
#include "playlist.h"
#include <QFile>
#include <QDir>
#include <QStringList>

#include <QDirIterator>
#include <QMessageBox>
#include <QUrl>

class M3uTranslator
{
public:

    M3uTranslator();
    static Playlist* getPlaylistFromM3u(QString absoluteFilename);
    static QStringList getPlaylists();
    static void savePlaylistToM3u(Playlist* playlist, QString absoluteFilename);

    static QString playlistNameToAbsPath(QString playlistname);

    static const QString DirName;

private:


};

#endif // M3UTRANSLATOR_H
