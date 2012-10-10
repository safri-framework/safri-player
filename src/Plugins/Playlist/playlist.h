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
    explicit Playlist(QList<Item*> items, QObject *parent = 0);
    explicit Playlist(QString m3ufile, QObject *parent = 0);



    void setShuffle(bool value);
    bool getShuffle();
    bool isCurrentMedia(int value);
    void moveMedia(int from, int to);
    void setCurrentMedia(int pos);
    void deleteMedia(int pos);
    void insertMediaAt(int position, QList<Song *> songs);
    bool isSafedPlaylist();


    Media* getMediaAt(int value);
    Media* getNextMedia();
    Media* getPreviousMedia();
    Media* getCurrentMedia();

    int getSize();

    void readTagsAtPosition(int position);
    void disconnectPlaylist();

private:

    bool safedPlaylist;
    int currentMedia;
    QList<Media*> mediaList;



    QReadWriteLock playlistLock;

    bool currentMediaTransactionRequested;
    int  currentMediaTransaction;

    void checkCurrentMediaTransaction();

    QList<Media*> shuffleHistory;
    bool shuffle;
    int shuffleCounter;
    QList<Media*> shufflePlaylist(QList<Media*> media);


signals:

    void changeActualPlayingMarker(int from, int to);

    void MediaInserted(int position, int count);

    void MediaMoved(int from, int to);

    void MediaDeleted(int value);

    void MediaDataChanged(int value);



};
#endif // PLAYLIST_H
