#include "SpotifyMediaBackend.h"
#include <QDebug>
SpotifyMediaBackend::SpotifyMediaBackend(QObject *parent):IMediaBackend(parent),
    _session(QSpotifySession::instance()),
  _cache(QSpotifyCacheManager::instance())
{
    connect(_session, SIGNAL(currentTrackPositionChanged()), this, SLOT(updateTrackPos()));
    connect(_session, SIGNAL(isPlayingChanged()), this, SLOT(updateState()));
    connect(_session, SIGNAL(trackFinished()), this, SIGNAL(mediaFinished()));

}

int SpotifyMediaBackend::getTotalTime()
{
    if(_session->hasCurrentTrack())
        return _session->currentTrack()->duration();

    return -1;
}

int SpotifyMediaBackend::getCurrentTime()
{
    if(_session->hasCurrentTrack())
        return _session->currentTrackPosition();

    return -1;
}

void SpotifyMediaBackend::seek(int ms)
{
    if(_session->hasCurrentTrack())
        _session->seek(ms);
}

void SpotifyMediaBackend::play(QUrl url)
{
    std::shared_ptr<QSpotifyTrack> track;
    //connect(track.get(), SIGNAL())
    QString test = url.toString().remove("file:");
    qDebug()<<test;

    track =_cache.getTrack(sp_link_as_track(sp_link_create_from_string(test.toUtf8())));
    if(track)
        _session->play(track);
}

void SpotifyMediaBackend::play()
{
    Q_EMIT hasSeekableMedia(true);
    _session->resume();
}

void SpotifyMediaBackend::pause()
{
    if(_session->isPlaying())
        _session->pause();
}

void SpotifyMediaBackend::stop()
{

    if(_session->isPlaying())
        _session->stop();
}

void SpotifyMediaBackend::setVolume(int percent)
{
    Q_UNUSED( percent )
}

int SpotifyMediaBackend::getVolume()
{
    return 0;
}

QStringList SpotifyMediaBackend::getSupportedMimeTypes()
{
    QStringList mimeTypes;
    mimeTypes += "spotify";
    return mimeTypes;
}

void SpotifyMediaBackend::updateTrackPos()
{
    qDebug()<<"TRACKPOS";
    Q_EMIT update(_session->currentTrackPosition());
}


void SpotifyMediaBackend::updateState()
{
    if(_session->isPlaying())
        Q_EMIT internalBackendStateChanged(Core::IMediaBackend::PLAYING);
    else
    {
        if(_session->hasCurrentTrack())
            Q_EMIT internalBackendStateChanged(Core::IMediaBackend::STOPPED);
        else
            Q_EMIT internalBackendStateChanged(Core::IMediaBackend::PAUSED);
    }


    /*
//    switch (status)
//    {
//        case QMediaPlayer::LoadedMedia:
//                break;

//        case QMediaPlayer::EndOfMedia:
//                Q_EMIT mediaFinished();
//                break;
//        case QMediaPlayer::BufferingMedia:
//                Q_EMIT internalBackendStateChanged(Core::IMediaBackend::BUFFERING);
//                break;
//        case QMediaPlayer::BufferedMedia:
//                Q_EMIT internalBackendStateChanged(Core::IMediaBackend::PLAYING);
//                break;
//        case QMediaPlayer::StoppedState:
//                Q_EMIT internalBackendStateChanged(Core::IMediaBackend::STOPPED);
//                break;
//        case QMediaPlayer::PausedState:
//                Q_EMIT internalBackendStateChanged(Core::IMediaBackend::PAUSED);
//                break;
//            default:
//            qDebug()<<status;
//    }*/
}

