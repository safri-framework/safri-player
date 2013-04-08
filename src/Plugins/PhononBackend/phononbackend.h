#ifndef PHONONBACKEND_H
#define PHONONBACKEND_H

#include "Interfaces/IMediaBackend.h"
//#include <phonon>
#include <QMediaPlayer>
#define Qt5


class PhononBackend : public Core::IMediaBackend
{
    Q_OBJECT
    public:


        PhononBackend(QObject* parent = 0);


        virtual int getTotalTime();
        virtual int getCurrentTime();
        virtual void seek(int ms);
        virtual void play(QUrl url);
        virtual void play();
        virtual void pause();
        virtual void stop();
        virtual void setVolume(int percent);
        virtual int getVolume();
        virtual QStringList getSupportedMimeTypes();

    private:

#ifndef Qt5
        Phonon::MediaObject *mediaObject;
        Phonon::AudioOutput *audioOutput;
#endif

#ifdef Qt5
        QMediaPlayer* player;
#endif


    private slots:

        void tick(qint64 ms);
        void mediaStatusChanged(QMediaPlayer::MediaStatus status);
};

#endif // PHONONBACKEND_H
