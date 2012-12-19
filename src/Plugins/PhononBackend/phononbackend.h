#ifndef PHONONBACKEND_H
#define PHONONBACKEND_H

#include "Interfaces/IAudioBackend.h"
#include <phonon>

class PhononBackend : public Core::IAudioBackend
{
    Q_OBJECT
    public:


        PhononBackend();

        virtual int getTotalTime();
        virtual int getCurrentTime();
        virtual void seek(int ms);
        virtual void play(QUrl url);
        virtual void play();
        virtual void pause();
        virtual void stop();
        virtual void setVolume(int percent);
        virtual int getVolume();

    private:

        Phonon::MediaObject *mediaObject;
        Phonon::AudioOutput *audioOutput;

    private slots:

        void tick(qint64 ms);
};

#endif // PHONONBACKEND_H
