#ifndef QSPOTIFYAUDIOTHREADWORKER_H
#define QSPOTIFYAUDIOTHREADWORKER_H

#include <QtCore/QObject>
#include <QtCore/QBuffer>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <QtCore/QHash>
#include <QtGui/QImage>

#ifdef __APPLE__
 #include <Headers/api.h>
#else
    #include <libspotify/api.h>
#endif


#include "qspotifyringbuffer.h"

#define AUDIOSTREAM_UPDATE_INTERVAL 20

extern QSpotifyRingbuffer g_buffer;
extern QMutex g_mutex;

extern QMutex g_imageRequestMutex;
extern QHash<QString, QWaitCondition *> g_imageRequestConditions;
extern QHash<QString, QImage> g_imageRequestImages;
extern QHash<sp_image *, QString> g_imageRequestObject;

class QAudioOutput;
class QIODevice;

class QSpotifyAudioThreadWorker : public QObject
{
public:
    QSpotifyAudioThreadWorker(QObject *parent = nullptr);

    bool event(QEvent *);

private:
    void startStreaming(int channels, int sampleRate);
    void updateAudioBuffer();
    void startAudioOutput();

    QAudioOutput *m_audioOutput;
    QIODevice *m_iodevice;
    int m_audioTimerID;
    int m_timeCounter;
    int m_previousElapsedTime;
};

#endif // QSPOTIFYAUDIOTHREADWORKER_H
