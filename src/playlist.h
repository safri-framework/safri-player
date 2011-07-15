
#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "audiofile.h"


#include <QObject>
#include <QReadWriteLock>


/**
    \brief  This class provides basic playlist functionality.


*/
class Playlist : public QObject
{
    Q_OBJECT
public:
    explicit Playlist(QList<AudioFile*> *audioFiles, QObject *parent = 0);

    void setShuffle(bool value); 
    bool isSongPlaying(int value);
    void moveSong(int from, int to);
    void setCurrentPlayingSong(int value);
    void deleteSong(int value);
    void insertSongsAt(int position, QList<AudioFile*> *songs);

    void sortByArtist(Qt::SortOrder order);
    void sortByTitle(Qt::SortOrder order);
    void sortByYear(Qt::SortOrder order);
    void sortByGenre(Qt::SortOrder order);
    void sortByTrack(Qt::SortOrder order);
    void sortByAlbum(Qt::SortOrder order);

    static bool ArtistAtoZ(AudioFile* file1, AudioFile* file2);
    static bool ArtistZtoA(AudioFile* file1, AudioFile* file2);
    static bool GenreAtoZ(AudioFile* file1, AudioFile* file2);
    static bool GenreZtoA(AudioFile* file1, AudioFile* file2);
    static bool TitleAtoZ(AudioFile* file1, AudioFile* file2);
    static bool TitleZtoA(AudioFile* file1, AudioFile* file2);
    static bool Year0toX(AudioFile* file1, AudioFile* file2);
    static bool YearXto0(AudioFile* file1, AudioFile* file2);
    static bool Track0toX(AudioFile* file1, AudioFile* file2);
    static bool TrackXto0(AudioFile* file1, AudioFile* file2);
    static bool AlbumAtoZ(AudioFile* file1, AudioFile* file2);
    static bool AlbumZtoA(AudioFile* file1, AudioFile* file2);

    AudioFile* getAudioFileAt(int value);
    AudioFile* getNextSong();
    AudioFile* getPreviousSong();
    AudioFile* getCurrentPlayingAudioFile();

    int getSongCount();

    void readTagsAtPosition(int position);
    void disconnectPlaylist();

private:

    int actualPlayingSong;
    QList<AudioFile*> *SongList;
    bool shuffle;

    QReadWriteLock playlistLock;

    bool actualPlayingSongTransactionRequested;
    int  actualPlayingSongTransaction;

    void checkActualPlayingSongTransaction();


signals:

    void positionOfActuallyPlayingSongChanged(int from, int to);
    void songsInserted(int position, int count);
    void songMoved(int from, int to);
    void songDeleted(int value);
    void songDataChanged(int value);


};

#endif // PLAYLIST_H

