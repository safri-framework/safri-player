#include "icore.h"
#include "pluginmanager.h"
#include "iplaybackcontroller.h"
#include "Interfaces/IAudioBackend.h"
#include "Interfaces/IPlaylistFactory.h"

#include <QDebug>

using namespace Core;

ICore* ICore::m_instance;

ICore::ICore()
{
    qDebug() << "ICore()";
    connect(PluginSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)), this, SLOT(objectAddedToObjectPool(QObject*)));
}

ICore *ICore::instance()
{
    return m_instance;
}

IPlaybackController* ICore::playbackController()
{
    return m_instance->m_playbackController;
}

IAudioBackend *ICore::audioBackend()
{
    return m_instance->m_audioBackend;
}

void ICore::objectAddedToObjectPool(QObject *object)
{
    IPlaybackController *pbc = qobject_cast<IPlaybackController*>(object);
    if (pbc != 0)
    {
        qDebug() << "IPlaybackController class added";
        m_playbackController = pbc;
    }

    IAudioBackend *audio_backend = qobject_cast<IAudioBackend*>(object);
    if (audio_backend != 0)
    {
        qDebug() << "IAudioBackend class added";
        m_audioBackend = audio_backend;
    }

    IPlaylistFactory *playlistFactory = qobject_cast<IPlaylistFactory*>(object);
    if (playlistFactory != 0)
    {
        m_playlistFactory = playlistFactory;
    }
}

IPlaylist *ICore::createPlaylist()
{
    if (m_instance->m_playlistFactory != 0)
    {
        return m_instance->m_playlistFactory->createPlaylist();
    }

    return 0;
}


