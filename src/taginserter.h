#ifndef TAGINSERTER_H
#define TAGINSERTER_H

#include <QThread>
#include <QMutex>
#include "playlist.h"

/**
    \brief Reads all audiofile meta-tags from a playlist in a own thread.

    This helper class starts a thread and reads all meta-tags from the
    audiofiles in the given playlist. It responds to the playlist modified
    signals (song inserted/deleted ...) and adjust the current playlist tagging
    position if needed.

*/
class TagInserter : public QThread
{
    Q_OBJECT
    private:

        QMutex positionMutex;
        int currentPosition;
        Playlist *playlist;
        bool signalToStop;

    public:

        explicit TagInserter(Playlist *playlist, QObject *parent = 0);

        void run();
        void stop();

    public slots:

        void songsInserted(int position, int count);
        void songMoved(int from, int to);
        void songDeleted(int position);


};

#endif // TAGINSERTER_H



