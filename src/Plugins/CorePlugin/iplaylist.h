#ifndef IPLAYLIST_H
#define IPLAYLIST_H

#include <QObject>
#include "CorePlugin_global.h"
 class Song;
namespace Core
{
    class COREPLUGINSHARED_EXPORT IPlaylist : public QObject
    {
        Q_OBJECT
    public:
       // explicit IPlaylist(QObject *parent = 0);



        /**
            \brief enables or disables shuffle mode

            \param  'true' enables shuffle functionality, 'false' will disable it.

        */

        virtual void setShuffle(bool value) = 0;

        /**
            \brief returns 'true' if shuffle mode is enabled.
        */

        virtual bool getShuffle() = 0;

        /**

            \brief returns 'true' if the song on the given position is marked as 'playing'
        */

        virtual bool isSongPlaying(int value) = 0;

        /**
            \brief  This function will move the position of a song.


            \param  moveSong(2, 5) will move the second song to the fith position.
            \returns
        */

        virtual void moveSong(int from, int to) = 0;

        /**
            \brief  Will mark the song at the given position as "current playing"

            \param  position of that song as Integer.

        */

        virtual void setCurrentPlayingSong(int value) = 0;

        /**
            \brief  Will remove the song at given position from playlist.

            \param  position of the song.

        */

        virtual void deleteSong(int value) = 0;

        /**
            \brief this function is for inserting songs into the playlist.

            \param  position is where the songs will be inserted, songs is a QList of songs which will be inserted.


        */

        virtual void insertSongsAt(int position, QList<Song *> songs) = 0;

        /**
            \brief  returns true, if that playlist was stored

            \param
            \returns
        */

        virtual bool isSafedPlaylist() = 0;

        /**
            \brief Returns the Song at given position.


            \returns the Song at given position.
        */

        virtual Song* getSongAt(int value) = 0;

        /**
            \brief returns the song which will be played next.

            If shuffle-mode is on, that song does not have to be the 'physical next' Song in the list. In fact,
            it has to return the next Song which should be played.

            \param
            \returns a Pizza with double cheese and bacon..
        */


        virtual Song* getNextSong() = 0;

        /**
            \brief  see also: getNextSong()


            \returns the previous Song in play-order
        */

        virtual Song* getPreviousSong() = 0;

        /**
            \brief  returns the song which is acutally playing.


            \returns a Song.
        */



        virtual Song* getCurrentPlayingSong() = 0;

        /**
            \brief  returns the count of songs in Playlist

            \param
            \returns an Integer
        */

        virtual int getSongCount()= 0;

        /**
            \brief  forces the Tagger to read the tags at that position

            \param
            \returns
        */

        virtual void readTagsAtPosition(int position) = 0;

        /**
            \brief

            \param
            \returns
        */

        virtual void disconnectPlaylist() = 0;

    signals:

       // void positionOfActuallyPlayingSongChanged(int from, int to);
        // was renamed in:

        /**
            \brief  lets the PlaylistModel know, that another ModelIndex has to be marked as "playing"
        */
        void changeActualPlayingMarker(int from, int to);
        /**
            \brief  this signal has to be emitted if songs were inserted.
        */

        void songsInserted(int position, int count);

        /**
            \brief  this signal has to be emitted if a song was moved.
        */

        void songMoved(int from, int to);

        /**
            \brief  this signal has to be emitted if a song was deleted.
        */
        void songDeleted(int value);

        /**
            \brief  this signal will force the PlaylistModel (ViewAdapter) to redraw the data of the given song.

        */

        void songDataChanged(int value);

    };
}

Q_DECLARE_INTERFACE(Core::IPlaylist, "IPlaylist")

#endif // IPLAYLIST_H
