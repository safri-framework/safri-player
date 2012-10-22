#ifndef IAUDIOBACKEND_H
#define IAUDIOBACKEND_H

#include "IMediaBackend.h"
#include <QObject>
#include <QUrl>

namespace Core
{
    class COREPLUGINSHARED_EXPORT IAudioBackend : public QObject, public IMediaBackend
    {
        Q_OBJECT
        public:

            virtual int getTotalTime() = 0;
            virtual int getCurrentTime() = 0;
            virtual void seek(int ms) = 0;
            virtual void play(QUrl url) = 0;
            virtual void play() = 0;
            virtual void pause() = 0;
            virtual void stop() = 0;
            virtual void setVolume(int percent) = 0;

        signals:

            void update(int currentTime);
            void playing();
            void paused();
            void stopped();
            void mediaFinished();
            void volumeChanged(int percent);
    };
}

Q_DECLARE_INTERFACE(Core::IAudioBackend, "Core::IAudioBackend")

#endif // IAUDIOBACKEND_H
