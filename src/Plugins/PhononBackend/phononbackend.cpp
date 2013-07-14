#include "phononbackend.h"

#include <QDebug>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>


PhononBackend::PhononBackend(QObject* parent):IMediaBackend(parent)
{
#ifndef Qt5
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    Phonon::createPath(mediaObject, audioOutput);

    mediaObject->setTickInterval(1000);
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(finished()), this, SIGNAL(mediaFinished()));
#endif

#ifdef Qt5
    qDebug()<<Q_FUNC_INFO;
    player = new QMediaPlayer(this);
    player->setVolume(100);
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(tick(qint64)));
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
#endif


}

int PhononBackend::getTotalTime()
{
    #ifndef Qt5
    // EVIL HACK: wait 'n pray....
    QTime dieTime = QTime::currentTime().addMSecs(500);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    return mediaObject->totalTime();
    #endif


#ifdef Qt5
#ifdef ANDROID
    // EVIL HACK: wait 'n pray....
    QTime dieTime = QTime::currentTime().addMSecs(500);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    return  player->duration();
#else
   return  player->duration();
#endif
#endif
}

int PhononBackend::getCurrentTime()
{
    #ifndef Qt5
    return mediaObject->currentTime();
    #endif

#ifdef Qt5
    return player->position();
#endif

}

void PhononBackend::seek(int ms)
{
    #ifndef Qt5
    qDebug() << "seek: " << QString::number(ms);
    mediaObject->seek(ms);

    #endif

#ifdef Qt5
    player->setPosition(ms);

#endif

    Q_EMIT update(ms);
}

void PhononBackend::play(QUrl url)
{
    qDebug()<<Q_FUNC_INFO<<""<<url;
    #ifndef Qt5
    Q_EMIT hasSeekableMedia(true);
    Q_EMIT hasVolumeAdjustableMedia(true);
    mediaObject->setCurrentSource(Phonon::MediaSource(url));
    mediaObject->play();
    qDebug() << "PhononBackend::play: " << url.toString();
    #endif

#ifdef Qt5
    Q_EMIT hasSeekableMedia(player->isSeekable());
    Q_EMIT hasVolumeAdjustableMedia(true);
    player->setMedia(QMediaContent());
    player->setMedia(url);
    player->play();

#endif
}

void PhononBackend::play()
{
    #ifndef Qt5
    mediaObject->play();
    #endif

#ifdef Qt5
    qDebug()<<"PLAY";
    player->play();
#endif
}

void PhononBackend::pause()
{
    #ifndef Qt5
    mediaObject->pause();
    #endif

#ifdef Qt5
    player->pause();
#endif
}

void PhononBackend::stop()
{
    #ifndef Qt5
    mediaObject->stop();
    #endif

#ifdef Qt5
    player->stop();
#endif
}

void PhononBackend::setVolume(int percent)
{
    #ifndef Qt5
    audioOutput->setVolume(percent / 100.0f);
    #endif

#ifdef Qt5
    player->setVolume(percent);
#endif
}

int PhononBackend::getVolume()
{
    #ifndef Qt5
    return audioOutput->volume() * 100.0f;
    #endif

#ifdef Qt5
    // TODO:
    //if(player->volume() > 0)
    {
        //qDebug()<<"VOLUME!!?";
        return player->volume();
    }
    //else
    {
    //    return 100;
    }
#endif
}

QStringList PhononBackend::getSupportedMimeTypes()
{
    #ifndef Qt5
    return Phonon::BackendCapabilities::availableMimeTypes();
    #endif
    #ifdef Qt5

        qDebug()<<player->supportedMimeTypes();
        QStringList list;
        list.append("audio/mpeg");
        //return player->supportedMimeTypes();
        return list;
    #endif
}

void PhononBackend::tick(qint64 ms)
{
    //qDebug() << QString::number(getCurrentTime() / 1000.0f);

    Q_EMIT update(ms);


}

void PhononBackend::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status)
    {
        case QMediaPlayer::EndOfMedia:
            Q_EMIT mediaFinished();
            break;
    case QMediaPlayer::BufferingMedia:
            Q_EMIT internalBackendStateChanged(Core::IMediaBackend::BUFFERING);
            break;
    case QMediaPlayer::BufferedMedia:
            Q_EMIT internalBackendStateChanged(Core::IMediaBackend::PLAYING);
            break;
    case QMediaPlayer::StoppedState:
            Q_EMIT internalBackendStateChanged(Core::IMediaBackend::STOPPED);
            break;
    case QMediaPlayer::PausedState:
            Q_EMIT internalBackendStateChanged(Core::IMediaBackend::PAUSED);
            break;
        default:
        qDebug()<<status;



    }
}
