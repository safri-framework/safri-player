#ifndef SPOTIFYMEDIABACKEND_H
#define SPOTIFYMEDIABACKEND_H

#include "Interfaces/IMediaBackend.h"
#include "../libQtSpotify/QtSpotify"
#include "../libQtSpotify/qspotifycachemanager.h"
#include <QTimer>

using namespace Core;

class SpotifyMediaBackend : public IMediaBackend
{

    Q_OBJECT

public:
    SpotifyMediaBackend(QObject* parent = 0);
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
    QSpotifySession* _session;
    QSpotifyCacheManager& _cache;
    QTimer* _timer;

private slots:
    void updateTrackPos();
    void updateState();
};

#endif // SPOTIFYMEDIABACKEND_H
