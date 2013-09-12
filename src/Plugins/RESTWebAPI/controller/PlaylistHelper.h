#ifndef PLAYLISTHELPER_H
#define PLAYLISTHELPER_H

#include <QMainWindow>
#include <QSharedPointer>
#include "Interfaces/IPlaylist.h"
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
    void deleteItem(int pos);
    void playItem(int index);
    void setShuffle(bool value);
    void moveSong(int fromPos, int toPos);

    void setAsCurrent();

    int getCurrentVersionID();
    int getCurrentPlayingSongIndex();
    int getCurrentPlaylistSize();

    QSharedPointer<Core::IPlaylist> getPlaylistInstance();

    QJsonArray getCurrentPlaylist();
    QJsonArray getPlayingPlaylist();

signals:
    
public slots:

private slots:
    void playlistDataChanged();
    void playerHasNewPlaylist();
    
private:
    static PlaylistHelper* instance;
    explicit PlaylistHelper(QWidget *parent = 0);
    QSharedPointer<Core::IPlaylist> currentPlaylist;
    static QMutex mutex;
    int versionID;


};

#endif // PLAYLISTHELPER_H
