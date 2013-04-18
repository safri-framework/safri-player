#ifndef IPLAYBACKCONTROLLER_H
#define IPLAYBACKCONTROLLER_H

#include "CorePlugin_global.h"

#include <QObject>
#include <QtWidgets/QAction>

namespace Core
{

    enum playState{PLAY, STOP, PAUSE, NODATA, BUFFERING};

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
            virtual void setPlaylist(QSharedPointer<IPlaylist>) = 0;

            /**
                \returns the current playlist
            */
            virtual QSharedPointer<IPlaylist> getPlaylist() = 0;

            /**
                \brief  will start to play the current media from the playlist
            */
            virtual QAction* playAction() = 0;

            /**
                \brief  will pause the current media
            */
            virtual QAction* pauseAction() = 0;

            /**
                \brief  will stop the current media
            */
            virtual QAction* stopAction() = 0;

            /**
                \brief  will start to play the next media from the playlist
            */
            virtual QAction* nextAction() = 0;

            /**
                \brief  will start to play the previous media from the playlist
            */
            virtual QAction* previousAction() = 0;

            virtual QAction* playPauseAction() = 0;

            virtual QList<QAction*> getAdditionalActions() = 0;

            virtual int getMediaTotalTime() = 0;

            virtual int getVolume() = 0;

        signals:

            /**
                \brief  emit this signal whenever the current media has changed
            */
            void mediaChanged(Core::Media*);

            /**
                \brief  this signal can be used to update your disply in the GUI
            */
            void update(int currentTime);

            void stateChanged(Core::playState state);

            void hasSeekableMedia(bool value);

            void hasVolumeAdjustableMedia(bool value);

            void newPlaylistInstalled(QSharedPointer<Core::IPlaylist>);

        private slots:

                virtual void playStateSlot() = 0;
                virtual void pauseStateSlot()= 0;
                virtual void stopStateSlot() = 0;
                virtual void currentSongFinished() = 0;
                virtual void noDataSlot() = 0;

        public slots:

                virtual void seek(int playTime) = 0;
                virtual void setVolume(int volume) = 0;

    };

}

Q_DECLARE_INTERFACE(Core::IPlaybackController, "Core::IPlaybackController")

#endif // IPLAYBACKCONTROLLER_H
