#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "iplaylist.h"
#include "CoreData/song.h"
#include <QList>
#include "CoreData/song.h"

using namespace Core;
class Playlist : public Core::IPlaylist
{
    Q_OBJECT
    Q_INTERFACES(Core::IPlaylist)

public:
    explicit Playlist(QList<Song*> songs, QObject *parent = 0);
    explicit Playlist(QString m3ufile, QObject *parent = 0);



    void setShuffle(bool value);
    bool getShuffle();
    bool isItemPlaying(int value);
    void moveItem(int from, int to);
    void setCurrentPlayingItem(int value);
    void deleteItem(int value);
    void insertItemsAt(int position, QList<Song *> songs);
    bool isSafedPlaylist();


    Song* getItemAt(int value);
    Song* getNextItem();
    Song* getPreviousItem();
    Song* getCurrentPlayingItem();

    int getItemCount();

    void readTagsAtPosition(int position);
    void disconnectPlaylist();

private:

    bool safedPlaylist;
    int actualPlayingSong;
    QList<Song*> SongList;



    QReadWriteLock playlistLock;

    bool actualPlayingSongTransactionRequested;
    int  actualPlayingSongTransaction;

    void checkActualPlayingSongTransaction();

    QList<Song*> shuffleHistory;
    bool shuffle;
    int shuffleCounter;
    QList<Song*> shufflePlaylist(QList<Song*> songs);


signals:

    void positionOfActuallyPlayingSongChanged(int from, int to);
    void songsInserted(int position, int count);
    void songMoved(int from, int to);
    void songDeleted(int value);
    void songDataChanged(int value);


};
#endif // PLAYLIST_H
