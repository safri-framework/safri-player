

#include "playlist.h"
#include <cstdlib>
#include <qglobal.h>
#include <QFile>

using namespace Core;

Playlist::Playlist(QObject *parent) :
    IPlaylist(parent), safedPlaylist(false), currentMedia(-1), currentMediaTransactionRequested(false), currentMediaTransaction(0), shuffle(false), shuffleCounter(-1)
{

}


Playlist::Playlist(QList<Item*> items, QObject *parent) :
   IPlaylist(parent), safedPlaylist(false), currentMedia(-1), currentMediaTransactionRequested(false), currentMediaTransaction(0), shuffle(false), shuffleCounter(-1)
{

    for(int i = 0; i < items.size(); i++)
    {
        mediaList.append(items.at(i)->getMedia());
    }
}

Playlist::Playlist(QString m3ufile, QObject *parent) :
       IPlaylist(parent), safedPlaylist(true),  currentMedia(-1), currentMediaTransactionRequested(false), currentMediaTransaction(0), shuffle(false), shuffleCounter(-1)
{
/*

    QFile m3u( m3ufile );

    m3u.open(QIODevice::ReadOnly);
    QTextStream fileStream(&m3u);
    while (!fileStream.atEnd())
    {
        QString path = fileStream.readLine();
        if (path.at(0)!='#') SongList.append(new AudioFile(path));
    }


*/
}




void Playlist::checkCurrentMediaTransaction()
{
    if (currentMediaTransactionRequested)
    {
        currentMedia = currentMediaTransaction;
        currentMediaTransactionRequested = false;
    }
}

Media* Playlist::getNextMedia()
{

    Media* media;
    playlistLock.lockForRead();

        checkCurrentMediaTransaction();

        int nextMedia = currentMedia;
            if (!(shuffle))
            {

               if (nextMedia < mediaList.size()-1)
               {
                    nextMedia = currentMedia +1;
               }

            }
            else //todo!!
            {
                if (shuffleCounter < shuffleHistory.size()-1) shuffleCounter++;
               nextMedia = mediaList.indexOf(shuffleHistory.at(shuffleCounter));


            }

        setCurrentMedia(nextMedia);
        media = mediaList.at(nextMedia);

    playlistLock.unlock();
    return media;

}

Media* Playlist::getPreviousMedia()
{
Media* media = 0;

playlistLock.lockForRead();

    checkCurrentMediaTransaction();

    int previousMedia = currentMedia;
        if (!shuffle)
        {
            if (currentMedia > 0)
            {
                previousMedia = currentMedia-1;

            }

        }
        else // todo!!
        {
            if (shuffleCounter > 0)shuffleCounter --;
             previousMedia = mediaList.indexOf(shuffleHistory.at(shuffleCounter));


        }

    setCurrentMedia(previousMedia);
    media =  mediaList.at(previousMedia);
playlistLock.unlock();

return media;

}

void Playlist::setShuffle(bool value)
{

    shuffle = value;

    if (value && mediaList.size() > 0)
    {
        shuffleHistory.clear();
        shuffleHistory.append(mediaList);

        if(currentMedia >= 0) shuffleHistory.removeAt(currentMedia);
        shuffleHistory = shufflePlaylist(shuffleHistory);

    }
    else
    {
        shuffleHistory.clear();
    }

}

bool Playlist::getShuffle()
{

    return shuffle;

}




Media* Playlist::getMediaAt(int value)
{
    Media* media = 0;

    playlistLock.lockForRead();

        if (value >= 0 && value < mediaList.size())
        {
            media = mediaList.at(value);
        }

    playlistLock.unlock();

    return media;
}

void Playlist::moveMedia(int from, int to)
{
    playlistLock.lockForWrite();
        mediaList.move(from, to);
    playlistLock.unlock();

    Q_EMIT MediaMoved(from, to);

    // if necessary recalculate the position of the current playing song
    if (!(from == currentMedia))
    {
        if(from > currentMedia && to <= currentMedia)
        {
            setCurrentMedia(currentMedia+1);

        }
        else if(from < currentMedia && to >= currentMedia)
        {
            setCurrentMedia(currentMedia-1);

        }
    }
    else
    {
        setCurrentMedia(to);
    }

}

bool Playlist::isCurrentMedia(int value)
{
    return(value == currentMedia);
}

void Playlist::setCurrentMedia(int value)
{
    if (value < 0)
    {
        int lastMedia = currentMedia;
        this->currentMedia = -1;
        Q_EMIT(MediaDataChanged(lastMedia));

    }
    else
    {
        if(currentMedia != value)
        {
            int lastMedia = currentMedia;

            currentMedia = value;
            currentMediaTransactionRequested = false;

            Q_EMIT changeActualPlayingMarker(lastMedia, currentMedia);
        }
    }
}

void Playlist::deleteMedia(int value)
{
    playlistLock.lockForWrite();

        mediaList.removeAt(value);

    playlistLock.unlock();

    // if necessary recalculate the position of the current playing song
    if(value < currentMedia)
    {
        setCurrentMedia(currentMedia -1);
    }

    // if actual playing song was deleted we want the view
    // to remove the playing icon from the playlist
    // so temporarily we set the current playing song to -1

    if ( (value == currentMedia) )
    {
        // but when the current playing song finished we want the
        // playlist to continues with the next song that was actualy after
        // the deleted song

        // so we store the position of that next song
        currentMediaTransaction = currentMedia - 1;
        setCurrentMedia(-1);

        // and set a transaction flag which we check in getNext/Previous Item
        // and restore the position of that next song
        currentMediaTransactionRequested = true;
    }


    Q_EMIT MediaDeleted(value);
}


void Playlist::insertMediaAt(int position, QList<Item*> items)
{
    QList<Media*> media;
    for(int i = 0; i < items.size(); i++)
    {
        media.append(items.at(i)->getMedia());
    }


    if (position < mediaList.size())
    {
        playlistLock.lockForWrite();

            for (int i = 0; i < media.size(); i++)
            {
                mediaList.insert(i + position , media.at(i));

            }

        playlistLock.unlock();

        if(position <= currentMedia)
        {
            setCurrentMedia(currentMedia + media.size());
        }

    }
    else
    {
        playlistLock.lockForWrite();
            mediaList.append(media);
        playlistLock.unlock();
    }


    if (shuffle)
    {
        QList<Media*> temp;
        for (int i = shuffleCounter +1; i < shuffleHistory.size(); i++)
        {
            temp.append(shuffleHistory.at(i));
            shuffleHistory.removeAt(i);
        }
        temp.append(media);



        shuffleHistory.append(shufflePlaylist(media));

    }

    Q_EMIT MediaInserted(position, media.size());
}

void Playlist::appendMedia(Media* media)
{
    int position = mediaList.size();

    playlistLock.lockForWrite();
        mediaList.append(media);
    playlistLock.unlock();

    if (shuffle)
    {
        QList<Media*> temp;
        for (int i = shuffleCounter +1; i < shuffleHistory.size(); i++)
        {
            temp.append(shuffleHistory.at(i));
            shuffleHistory.removeAt(i);
        }
        temp.append(media);

        shuffleHistory.append(media);
    }

    Q_EMIT MediaInserted(position, 1);
}

int Playlist::getCurrentMediaPosition()
{
    return currentMedia;
}



int Playlist::getSize()
{
    return mediaList.size();
}

void Playlist::readTagsAtPosition(int position)
{
/*

  TODO

   playlistLock.lockForRead();

     if (SongList.at(position)->ReadTags() >= 0)
     {
        Q_EMIT songDataChanged(position);
        playlistLock.unlock();
     }
     else
     {
         playlistLock.unlock();
         deleteSong(position);
     }

*/

}

Media* Playlist::getCurrentMedia()
{
    if(this->currentMedia == -1)
        this->currentMedia++;

    return getMediaAt(currentMedia);

}



QList<Media*> Playlist::shufflePlaylist(QList<Media *> media)
{


    for (int i = media.size()-1; i >= 0; i--)
    {

          int j = (int) (((float)qrand()/RAND_MAX) * i);
          media.swap(j, i);
     }

    return media;

}





void Playlist::disconnectPlaylist()
{
    this->setCurrentMedia(-1);


}



bool Playlist::isSafedPlaylist()
{
    return safedPlaylist;
}


