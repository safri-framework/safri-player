#ifndef IAUDIOBACKEND_H
#define IAUDIOBACKEND_H

#include "../CorePlugin_global.h"
#include <QObject>
#include <QUrl>

namespace Core
{
    class COREPLUGINSHARED_EXPORT IMediaBackend : public QObject
    {
        Q_OBJECT

        protected:
            IMediaBackend(QObject* parent);

        public:

            virtual int getTotalTime();
            virtual int getCurrentTime();
            virtual void seek(int ms);
            virtual void play(QUrl url) = 0;
            virtual void play() = 0;
            virtual void pause();
            virtual void stop() = 0;
            virtual void setVolume(int percent);
            virtual int getVolume();
            virtual QStringList getSupportedMimeTypes() = 0;

        signals:

            void update(int currentTime);
            void playing();
            void paused();
            void stopped();
            void mediaFinished();
            void volumeChanged(int percent);
            virtual void hasSeekableMedia(bool value);
            virtual void hasVolumeAdjustableMedia(bool value);
    };



}

Q_DECLARE_INTERFACE(Core::IMediaBackend, "Core::IMediaBackend")

#endif // IAUDIOBACKEND_H
