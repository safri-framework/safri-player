

#include "playlist.h"

Playlist::Playlist(QList<AudioFile*> *audioFiles, QObject *parent) :
    QObject(parent), actualPlayingSong(-1), SongList(audioFiles), shuffle(false), actualPlayingSongTransactionRequested(false), actualPlayingSongTransaction(0)
{

    if (SongList == 0)
    {
        SongList = new QList<AudioFile*>();
    }

}

void Playlist::checkActualPlayingSongTransaction()
{
    if (actualPlayingSongTransactionRequested)
    {
        actualPlayingSong = actualPlayingSongTransaction;
        actualPlayingSongTransactionRequested = false;
    }
}

AudioFile* Playlist::getNextSong()
{

    AudioFile* song;
    playlistLock.lockForRead();

        checkActualPlayingSongTransaction();

        int nextSong = actualPlayingSong;
            if (!(shuffle))
            {

               if (nextSong < SongList->size()-1)
               {
                    nextSong = actualPlayingSong +1;
               }

            }
            else //todo!!
            {

                nextSong = 0;


            }

        setCurrentPlayingSong(nextSong);
        song = SongList->at(nextSong);

    playlistLock.unlock();
    return song;

}

AudioFile* Playlist::getPreviousSong()
{
AudioFile* song = 0;

playlistLock.lockForRead();

    checkActualPlayingSongTransaction();

    int previousSong = actualPlayingSong;
        if (!shuffle)
        {
            if (actualPlayingSong > 0)
            {
                previousSong = actualPlayingSong-1;

            }

        }
        else // todo!!
        {
             previousSong = 0;

        }

    setCurrentPlayingSong(previousSong);
    song =  SongList->at(previousSong);
playlistLock.unlock();

return song;

}

void Playlist::setShuffle(bool value)
{
    shuffle = value;
}

AudioFile* Playlist::getAudioFileAt(int value)
{
    AudioFile* song = 0;

    playlistLock.lockForRead();

        if (value >= 0 && value < SongList->size())
        {
            song = SongList->at(value);
        }

    playlistLock.unlock();

    return song;
}

void Playlist::moveSong(int from, int to)
{
    playlistLock.lockForWrite();
        SongList->move(from, to);
    playlistLock.unlock();

    Q_EMIT songMoved(from, to);

    // if necessary recalculate the position of the current playing song
    if (!(from == actualPlayingSong))
    {
        if(from > actualPlayingSong && to <= actualPlayingSong)
        {
            setCurrentPlayingSong(actualPlayingSong+1);

        }
        else if(from < actualPlayingSong && to > actualPlayingSong)
        {
            setCurrentPlayingSong(actualPlayingSong-1);

        }
    }
    else
    {
        setCurrentPlayingSong(to);
    }

}

bool Playlist::isSongPlaying(int value)
{
    return(value == actualPlayingSong);
}

void Playlist::setCurrentPlayingSong(int value)
{
    if (value < 0)
    {
        int oldPlayingSong = actualPlayingSong;
        this->actualPlayingSong = -1;
        Q_EMIT(songDataChanged(oldPlayingSong));

    }
    else
    {
        if(actualPlayingSong != value)
        {
            int oldPlayingSong = actualPlayingSong;

            actualPlayingSong = value;
            actualPlayingSongTransactionRequested = false;

            Q_EMIT positionOfActuallyPlayingSongChanged(oldPlayingSong, actualPlayingSong);
        }
    }
}

void Playlist::deleteSong(int value)
{
    playlistLock.lockForWrite();

        SongList->removeAt(value);

    playlistLock.unlock();

    // if necessary recalculate the position of the current playing song
    if(value < actualPlayingSong)
    {
        setCurrentPlayingSong(actualPlayingSong -1);
    }

    // if actual playing song was deleted we want the view
    // to remove the playing icon from the playlist
    // so temporarily we set the current playing song to -1

    if ( (value == actualPlayingSong) )
    {
        // but when the current playing song finished we want the
        // playlist to continues with the next song that was actualy after
        // the deleted song

        // so we store the position of that next song
        actualPlayingSongTransaction = actualPlayingSong - 1;
        setCurrentPlayingSong(-1);

        // and set a transaction flag which we check in getNext/Previous Song
        // and restore the position of that next song
        actualPlayingSongTransactionRequested = true;
    }


    Q_EMIT songDeleted(value);
}


void Playlist::insertSongsAt(int position, QList<AudioFile*> *songs)
{
    if (position < SongList->size())
    {
        playlistLock.lockForWrite();

            for (int i = 0; i < songs->size(); i++)
            {
                SongList->insert(i + position , songs->at(i));

            }

        playlistLock.unlock();

        if(position <= actualPlayingSong)
        {
            setCurrentPlayingSong(actualPlayingSong + songs->size());
        }

    }
    else
    {
        playlistLock.lockForWrite();
            SongList->append(*songs);
        playlistLock.unlock();
    }

    Q_EMIT songsInserted(position, songs->size());
}



int Playlist::getSongCount()
{
    return SongList->size();
}

void Playlist::readTagsAtPosition(int position)
{

   playlistLock.lockForRead();

     if (SongList->at(position)->ReadTags() >= 0)
     {
        Q_EMIT songDataChanged(position);
        playlistLock.unlock();
     }
     else
     {
         playlistLock.unlock();
         deleteSong(position);
     }



}

AudioFile* Playlist::getCurrentPlayingAudioFile()
{
    return getAudioFileAt(actualPlayingSong);
}

bool Playlist::ArtistAtoZ(AudioFile* file1, AudioFile* file2)
{
    return file1->getArtist().toLower() < file2->getArtist().toLower();
}

bool Playlist::ArtistZtoA(AudioFile* file1, AudioFile* file2)
{
    return file1->getArtist().toLower() > file2->getArtist().toLower();
}

bool Playlist::GenreAtoZ(AudioFile* file1, AudioFile* file2)
{
    return file1->getGenre().toLower() < file2->getGenre().toLower();
}

bool Playlist::GenreZtoA(AudioFile* file1, AudioFile* file2)
{
    return file1->getGenre().toLower() > file2->getGenre().toLower();
}

bool Playlist::TitleAtoZ(AudioFile* file1, AudioFile* file2)
{
    return file1->getTitle().toLower() < file2->getTitle().toLower();
}

bool Playlist::TitleZtoA(AudioFile* file1, AudioFile* file2)
{
    return file1->getTitle().toLower() > file2->getTitle().toLower();
}

bool Playlist::Year0toX(AudioFile* file1, AudioFile* file2)
{
    return file1->getYear() < file2->getYear();
}

bool Playlist::YearXto0(AudioFile* file1, AudioFile* file2)
{
    return file1->getYear() > file2->getYear();
}

bool Playlist::Track0toX(AudioFile* file1, AudioFile* file2)
{
    return file1->getTrack() < file2->getTrack();
}

bool Playlist::TrackXto0(AudioFile* file1, AudioFile* file2)
{
    return file1->getTrack() > file2->getTrack();
}

bool Playlist::AlbumAtoZ(AudioFile* file1, AudioFile* file2)
{
    return file1->getAlbum().toLower() < file2->getAlbum().toLower();
}

bool Playlist::AlbumZtoA(AudioFile* file1, AudioFile* file2)
{
    return file1->getAlbum().toLower() > file2->getAlbum().toLower();
}

void Playlist::sortByArtist(Qt::SortOrder order)
{

    if (actualPlayingSong != -1)
    {
        AudioFile *currentSong = SongList->at(actualPlayingSong);
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::ArtistAtoZ);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::ArtistZtoA);
        }
        setCurrentPlayingSong(SongList->indexOf(currentSong));
    }
    else
    {
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::ArtistAtoZ);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::ArtistZtoA);
        }
    }

}

void Playlist::sortByAlbum(Qt::SortOrder order)
{

    if (actualPlayingSong != -1)
    {
        AudioFile *currentSong = SongList->at(actualPlayingSong);
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::AlbumAtoZ);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::AlbumZtoA);
        }
        setCurrentPlayingSong(SongList->indexOf(currentSong));
    }
    else
    {
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::AlbumAtoZ);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::AlbumZtoA);
        }
    }

}


void Playlist::sortByTitle(Qt::SortOrder order)
{
    if (actualPlayingSong != -1)
    {
        AudioFile *currentSong = SongList->at(actualPlayingSong);
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::TitleAtoZ);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::TitleZtoA);
        }
        setCurrentPlayingSong(SongList->indexOf(currentSong));
    }
    else
    {
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::TitleAtoZ);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::TitleZtoA);
        }
    }

}

void Playlist::sortByYear(Qt::SortOrder order)
{
    if (actualPlayingSong != -1)
    {
        AudioFile *currentSong = SongList->at(actualPlayingSong);
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::Year0toX);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::YearXto0);
        }
        setCurrentPlayingSong(SongList->indexOf(currentSong));
    }
    else
    {
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::Year0toX);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::YearXto0);
        }
    }
}

void Playlist::sortByGenre(Qt::SortOrder order)
{
    if (actualPlayingSong != -1)
    {
        AudioFile *currentSong = SongList->at(actualPlayingSong);
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::GenreAtoZ);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::GenreZtoA);
        }
        setCurrentPlayingSong(SongList->indexOf(currentSong));
    }
    else
    {
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::GenreAtoZ);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::GenreZtoA);
        }
    }
}

void Playlist::sortByTrack(Qt::SortOrder order)
{

    if (actualPlayingSong != -1)
    {
        AudioFile *currentSong = SongList->at(actualPlayingSong);
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::Track0toX);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::TrackXto0);
        }
        setCurrentPlayingSong(SongList->indexOf(currentSong));
    }
    else
    {
        if (order == Qt::AscendingOrder)
        {
            qSort(SongList->begin(), SongList->end(), Playlist::Track0toX);
        }
        else
        {
            qSort(SongList->begin(), SongList->end(), Playlist::TrackXto0);
        }
    }


}

void Playlist::disconnectPlaylist()
{
    this->setCurrentPlayingSong(-1);


}




