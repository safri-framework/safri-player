
#include "taginserter.h"

TagInserter::TagInserter(Playlist *playlist ,QObject *parent) :
    QThread(parent), currentPosition(0), playlist(playlist), signalToStop(false)
{

    connect(playlist, SIGNAL(songsInserted(int,int)), this, SLOT(songsInserted(int,int)));
    connect(playlist, SIGNAL(songMoved(int,int)), this, SLOT(songMoved(int,int)));
    connect(playlist, SIGNAL(songDeleted(int)), this, SLOT(songDeleted(int)));

}

void TagInserter::run()
{

    positionMutex.lock();
        currentPosition = 0;
    positionMutex.unlock();

    while (!signalToStop)
    {

         positionMutex.lock();

             if (currentPosition < playlist->getSongCount())
             {
                       playlist->readTagsAtPosition(currentPosition);
                       currentPosition++;
             }
             else
             {
                       positionMutex.unlock();
                       break;
             }

         positionMutex.unlock();



    }


    disconnect(playlist, SIGNAL(songsInserted(int,int)), this, SLOT(songsInserted(int,int)));
    disconnect(playlist, SIGNAL(songMoved(int,int)), this, SLOT(songMoved(int,int)));
    disconnect(playlist, SIGNAL(songDeleted(int)), this, SLOT(songDeleted(int)));

}


void TagInserter::stop()
{
    signalToStop = true;
}

void TagInserter::songsInserted(int position, int count)
{

    positionMutex.lock();

        // if there are songs inserted below the current position
        if (position <= currentPosition)
        {
            // these new songs has to be tagged, so set the current
            // position the the position where they had been inserted
            currentPosition = position;
        }


    positionMutex.unlock();
}

void TagInserter::songMoved(int from, int to)
{

    positionMutex.lock();

        if(from > currentPosition && to <= currentPosition)
        {
            currentPosition++;

        }
        else if(from < currentPosition && to > currentPosition)
        {
            currentPosition--;

        }

    positionMutex.unlock();

}

void TagInserter::songDeleted(int position)
{

    positionMutex.lock();

        // if there are songs deleted below the current position
        if (position < currentPosition)
        {
            // _untagged_ songs will move upwards the list and below the taggers currentPosition
            // so force the currentPosition to that deleted position that
            // the tagger will recheck the upwards moved songs
            currentPosition = position;
        }

    positionMutex.unlock();
}
