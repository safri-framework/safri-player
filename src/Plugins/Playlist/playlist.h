#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Playlist_global.h"
#include "iplaylist.h"
#include "CoreData/song.h"
#include <QList>
#include "CoreData/song.h"
#include <QReadWriteLock>

using namespace Core;
class PLAYLISTSHARED_EXPORT Playlist : public Core::IPlaylist
{
    Q_OBJECT
    Q_INTERFACES(Core::IPlaylist)

public:

    explicit Playlist(QObject *parent = 0);
    explicit Playlist(QList<Item*> items, QObject *parent = 0);
    explicit Playlist(QString plfile, QObject *parent = 0);
    ~Playlist();


    void setShuffle(bool value);
    bool getShuffle();
    bool isCurrentMedia(int value);
    void moveMedia(int from, int to);
    void setCurrentMedia(int pos);
    void deleteMedia(int pos);
    void insertMediaAt(int position, QList<Item *> items);
    void appendMedia(Media* media);
    int getCurrentMediaPosition();
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

    void changeCurrentPlayingMarker(int from, int to);

    void MediaInserted(int position, int count);

    void MediaMoved(int from, int to);

    void MediaDeleted(int value);

    void MediaDataChanged(int value);



};
#endif // PLAYLIST_H
