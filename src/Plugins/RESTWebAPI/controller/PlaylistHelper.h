#ifndef PLAYLISTHELPER_H
#define PLAYLISTHELPER_H

#include <QMainWindow>
#include <QSharedPointer>
#include "iplaylist.h"
#include <QJsonArray>
#include <QMutex>

namespace Core {
    class Item;
}

class PlaylistHelper : public QMainWindow
{
    Q_OBJECT
public:

    static PlaylistHelper* getInstance();
    void newPlaylist();
    bool appendItem(QString collection, int id, QString type = "org.safri.audio.song");
    bool insertItem(int pos, QString collection, int id, QString type = "org.safri.audio.song");
    bool insertItem(Core::Item* item, int pos);
    void moveSong(int fromPos, int toPos);
    void clearSong(int pos);
    void setAsCurrent();
    int getCurrentVersionID();
    QSharedPointer<Core::IPlaylist> getPlaylistInstance();

    QJsonArray getCurrentPlaylist();
    QJsonArray getPlayingPlaylist();

signals:
    
public slots:

private slots:
    void playlistDataChanged();
    void playerHasNewPlaylist(QSharedPointer<Core::IPlaylist> newPL);
    
private:
    static PlaylistHelper* instance;
    explicit PlaylistHelper(QWidget *parent = 0);
    QSharedPointer<Core::IPlaylist> currentPlaylist;
    static QMutex mutex;
    int versionID;


};

#endif // PLAYLISTHELPER_H
