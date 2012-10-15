#ifndef IPLAYBACKCONTROLLER_H
#define IPLAYBACKCONTROLLER_H

#include "CorePlugin_global.h"

#include <QObject>

namespace Core
{

    enum playState{PLAY, STOP, PAUSE, NODATA};

    class IPlaylist;
    class Media;

    /**
        \brief  Interface for playback controllers

        If you want to write your own playback controller, you have to implement
        this interface.
    */
    class COREPLUGINSHARED_EXPORT IPlaybackController : public QObject
    {
        Q_OBJECT
        public:

            /**
                \brief  sets the given playlist as current
                \param  the playlist
            */
            virtual void setPlaylist(IPlaylist*) = 0;

            /**
                \returns the current playlist
            */
            virtual IPlaylist* getPlaylist() = 0;

            /**
                \brief  will start to play the current media from the playlist
            */
            virtual void play() = 0;

            /**
                \brief  will pause the current media
            */
            virtual void pause() = 0;

            /**
                \brief  will stop the current media
            */
            virtual void stop() = 0;

            /**
                \brief  will start to play the next media from the playlist
            */
            virtual void next() = 0;

            /**
                \brief  will start to play the previous media from the playlist
            */
            virtual void previous() = 0;

        signals:

            /**
                \brief  emit this signal whenever the current media has changed
            */
            void mediaChanged(Media*);

            /**
                \brief  this signal can be used to update your disply in the GUI
            */

            void tick(int playTime);

            void stateChanged(playState state);


    public slots:


            virtual void seek(int playTime) = 0;
            virtual void playStateSlot() = 0;
            virtual void pauseStateSlot()= 0;
            virtual void stopStateSlot() = 0;
            virtual void currentSongFinished() = 0;
            virtual void noDataSlot() = 0;


    };

}

Q_DECLARE_INTERFACE(Core::IPlaybackController, "Core::IPlaybackController")

#endif // IPLAYBACKCONTROLLER_H
