#include "phononbackend.h"

#include <QDebug>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

PhononBackend::PhononBackend(QObject* parent):IMediaBackend(parent)
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    Phonon::createPath(mediaObject, audioOutput);

    mediaObject->setTickInterval(1000);
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(finished()), this, SIGNAL(mediaFinished()));
}

int PhononBackend::getTotalTime()
{
    // EVIL HACK: wait 'n pray....
    QTime dieTime = QTime::currentTime().addMSecs(500);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
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
    Q_EMIT hasSeekableMedia(true);
    Q_EMIT hasVolumeAdjustableMedia(true);
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

int PhononBackend::getVolume()
{
    return audioOutput->volume() * 100.0f;
}

QStringList PhononBackend::getSupportedMimeTypes()
{
    return Phonon::BackendCapabilities::availableMimeTypes();
}

void PhononBackend::tick(qint64 ms)
{
    //qDebug() << QString::number(getCurrentTime() / 1000.0f);
    Q_EMIT update(ms);
}
