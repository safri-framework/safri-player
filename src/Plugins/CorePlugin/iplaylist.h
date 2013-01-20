#ifndef IPLAYLIST_H
#define IPLAYLIST_H

#include <QObject>
#include "CorePlugin_global.h"

namespace Core
{

    class Item;
    class Media;

    class COREPLUGINSHARED_EXPORT IPlaylist : public QObject
    {
        Q_OBJECT
    public:

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

            \brief returns 'true' if the DataItem on the given position is marked as 'playing'
        */

        virtual bool isCurrentMedia(int value) = 0;

        /**
            \brief  This function will move the position of a Media.


            \param  moveMedia(2, 5) will move the second Media to the fith position.
            \returns
        */

        virtual void moveMedia(int from, int to) = 0;

        /**
            \brief  Will mark the Media at the given position as "current playing"

            \param  position of that Media as Integer.

        */
        virtual void setCurrentMedia(int value) = 0;

        /**
            \brief  Will remove the Media at given position from playlist.

            \param  position of the song.

        */
        virtual void deleteMedia(int value) = 0;

        /**
            \brief this function is for inserting Media into the playlist.

            \param  position is where the Media will be inserted, Media is a QList of Media which will be inserted.
        */
        virtual void insertMediaAt(int position, QList<Item*> items) = 0;

        virtual void appendMedia(Media* media) = 0;

        /**
            \brief  returns true, if that playlist was stored

            \param
            \returns
        */

        virtual bool isSafedPlaylist() = 0;

        /**
            \brief Returns the Media at given position.
            \returns the Media at given position.
        */

        virtual Media* getMediaAt(int value) = 0;

        /**
            \brief returns the Media which will be played next.

            If shuffle-mode is on, that Media does not have to be the 'physical next' Media in the list. In fact,
            it has to return the next Media which should be played.

            \param
            \returns a Pizza with double cheese and bacon..
        */
        virtual Media* getNextMedia() = 0;

        /**
            \brief  see also: getNextMedia()


            \returns the previous Media in play-order
        */

        virtual Media* getPreviousMedia() = 0;

        /**
            \brief  returns the Media which is acutally playing.


            \returns a pointer to Media.
        */
        virtual Media* getCurrentMedia() = 0;

        /**
            \brief  returns the count of Medias in Playlist

            \param
            \returns an Integer
        */
        virtual int getSize()= 0;

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


        virtual int getCurrentMediaPosition() = 0;

    signals:

       // void positionOfActuallyPlayingSongChanged(int from, int to);
        // was renamed in:

        /**
            \brief  lets the PlaylistModel know, that another ModelIndex has to be marked as "playing"
        */
        void changeActualPlayingMarker(int from, int to);

        /**
            \brief  this signal has to be emitted if Medias were inserted.
        */
        void MediaInserted(int position, int count);

        /**
            \brief  this signal has to be emitted if a Media was moved.
        */
        void MediaMoved(int from, int to);

        /**
            \brief  this signal has to be emitted if a Media was deleted.
        */
        void MediaDeleted(int value);

        /**
            \brief  this signal will force the PlaylistModel (ViewAdapter) to redraw the data of the given Media.

        */
        void MediaDataChanged(int value);

    protected:

        explicit IPlaylist(QObject *parent = 0) : QObject(parent) {}

    };
}

Q_DECLARE_INTERFACE(Core::IPlaylist, "IPlaylist")

#endif // IPLAYLIST_H
