#ifndef IPLAYLIST_H
#define IPLAYLIST_H

#include <QObject>
#include "CorePlugin_global.h"


 class Item;
 class Media;
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

            \brief returns 'true' if the BaseDTO on the given position is marked as 'playing'
        */

        virtual bool isCurrentMedia(int value) = 0;

        /**
            \brief  This function will move the position of a BaseDTO.


            \param  moveBaseDTO(2, 5) will move the second BaseDTO to the fith position.
            \returns
        */

        virtual void moveMedia(int from, int to) = 0;

        /**
            \brief  Will mark the BaseDTO at the given position as "current playing"

            \param  position of that BaseDTO as Integer.

        */

        virtual void setCurrentMedia(int value) = 0;

        /**
            \brief  Will remove the BaseDTO at given position from playlist.

            \param  position of the song.

        */

        virtual void deleteMedia(int value) = 0;

        /**
            \brief this function is for inserting BaseDTOs into the playlist.

            \param  position is where the BaseDTOs will be inserted, BaseDTOs is a QList of BaseDTOs which will be inserted.


        */

        virtual void insertMediaAt(int position, QList<Item*> items) = 0;

        /**
            \brief  returns true, if that playlist was stored

            \param
            \returns
        */

        virtual bool isSafedPlaylist() = 0;

        /**
            \brief Returns the BaseDTO at given position.


            \returns the BaseDTO at given position.
        */

        virtual Media* getMediaAt(int value) = 0;

        /**
            \brief returns the BaseDTO which will be played next.

            If shuffle-mode is on, that BaseDTO does not have to be the 'physical next' BaseDTO in the list. In fact,
            it has to return the next BaseDTO which should be played.

            \param
            \returns a Pizza with double cheese and bacon..
        */


        virtual Media* getNextMedia() = 0;

        /**
            \brief  see also: getNextBaseDTO()


            \returns the previous BaseDTO in play-order
        */

        virtual Media* getPreviousMedia() = 0;

        /**
            \brief  returns the BaseDTO which is acutally playing.


            \returns a pointer to BaseDTO.
        */



        virtual Media* getCurrentMedia() = 0;

        /**
            \brief  returns the count of BaseDTOs in Playlist

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

    signals:

       // void positionOfActuallyPlayingSongChanged(int from, int to);
        // was renamed in:

        /**
            \brief  lets the PlaylistModel know, that another ModelIndex has to be marked as "playing"
        */
        void changeActualPlayingMarker(int from, int to);
        /**
            \brief  this signal has to be emitted if BaseDTOs were inserted.
        */

        void MediaInserted(int position, int count);

        /**
            \brief  this signal has to be emitted if a BaseDTO was moved.
        */

        void MediaMoved(int from, int to);

        /**
            \brief  this signal has to be emitted if a BaseDTO was deleted.
        */
        void MediaDeleted(int value);

        /**
            \brief  this signal will force the PlaylistModel (ViewAdapter) to redraw the data of the given BaseDTO.

        */

        void MediaDataChanged(int value);

    };
}

Q_DECLARE_INTERFACE(Core::IPlaylist, "IPlaylist")

#endif // IPLAYLIST_H
