#include "phononbackend.h"

#include <QDebug>

PhononBackend::PhononBackend()
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    Phonon::createPath(mediaObject, audioOutput);

    mediaObject->setTickInterval(1000);
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
}

int PhononBackend::getTotalTime()
{
    return mediaObject->totalTime();
}

int PhononBackend::getCurrentTime()
{
    return mediaObject->currentTime();
}

void PhononBackend::seek(int ms)
{
    qDebug() << "seek: " << QString::number(ms);
    mediaObject->seek(ms);
    Q_EMIT update(ms);
}

void PhononBackend::play(QUrl url)
{
    mediaObject->setCurrentSource(Phonon::MediaSource(url));
    mediaObject->play();
    qDebug() << "PhononBackend::play: " << url.toString();
}

void PhononBackend::play()
{
    mediaObject->play();
}

void PhononBackend::pause()
{
    mediaObject->pause();
}

void PhononBackend::stop()
{
    mediaObject->stop();
}

void PhononBackend::setVolume(int percent)
{
    audioOutput->setVolume(percent / 100.0f);
}

void PhononBackend::tick(qint64 ms)
{
    //qDebug() << QString::number(getCurrentTime() / 1000.0f);
    Q_EMIT update(ms);
}
