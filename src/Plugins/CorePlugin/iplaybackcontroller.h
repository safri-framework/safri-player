#ifndef IPLAYBACKCONTROLLER_H
#define IPLAYBACKCONTROLLER_H

#include "CorePlugin_global.h"

#include <QObject>

namespace Core
{
    class IPlaylist;
    class Song;

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
                \brief  will start to play the current song an the playlist
            */
            virtual void play() = 0;

            /**
                \brief  will pause the current song
            */
            virtual void pause() = 0;

            /**
                \brief  will stop the current song
            */
            virtual void stop() = 0;

            /**
                \brief  will start to play the next song from the playlist
            */
            virtual void next() = 0;

            /**
                \brief  will start to play the previous song from the playlist
            */
            virtual void previous() = 0;

        signals:

            /**
                \brief  emit this signal whenever the currently playing song has changed
            */
            void songChanged(Song*);
    };

}

Q_DECLARE_INTERFACE(Core::IPlaybackController, "Core::IPlaybackController")

#endif // IPLAYBACKCONTROLLER_H
