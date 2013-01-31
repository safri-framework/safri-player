#include "icore.h"
#include "pluginmanager.h"
#include "iplaybackcontroller.h"
#include "Interfaces/IMediaBackend.h"
#include "Interfaces/IPlaylistFactory.h"
#include "Interfaces/iguicontroller.h"
#include "Interfaces/ICollectionController.h"

#include <QDebug>
#include <QDesktopServices>

using namespace Core;

ICore* ICore::m_instance = 0;

ICore::ICore()
    : m_playbackController(0), m_audioBackend(0), m_playlistFactory(0), m_guiController(0), m_collectionController(0)
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

IMediaBackend *ICore::audioBackend()
{
    qDebug() << "WARNING:deprecated function";
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

    IMediaBackend *media_backend = qobject_cast<IMediaBackend*>(object);
    if (media_backend != 0)
    {
        qDebug() << "IAudioBackend class added";
        m_audioBackend = media_backend;
    }

    IPlaylistFactory *playlistFactory = qobject_cast<IPlaylistFactory*>(object);
    if (playlistFactory != 0)
    {
        m_playlistFactory = playlistFactory;
    }

    IGUIController *guiController = qobject_cast<IGUIController*>(object);
    if (guiController != 0)
    {
        qDebug() << "ICore::IGUIController class added";
        m_guiController = guiController;
    }

    ICollectionController *collectionController = qobject_cast<ICollectionController*>(object);
    if (collectionController != 0)
    {
        qDebug() << "ICore::ICollectionController class added";
        m_collectionController = collectionController;
    }
}

QSharedPointer<IPlaylist> ICore::createPlaylist()
{
    if (m_instance->m_playlistFactory != 0)
    {
        return m_instance->m_playlistFactory->createPlaylist();
    }

    return QSharedPointer<IPlaylist>();
}

IGUIController *ICore::guiController()
{
    return m_instance->m_guiController;
}

ICollectionController *ICore::collectionController()
{
    return m_instance->m_collectionController;
}

QString ICore::storageDirectory()
{
    QString storageLocation = QDesktopServices::storageLocation(QDesktopServices::DataLocation);

#ifdef Q_OS_LINUX
    storageLocation.chop(2);
#endif

    return  storageLocation + "/.safri/";
}

IMediaBackend *ICore::getBackendForMedia(Media *media)
{
    return m_instance->m_mediaBackends.value(media->getMimeType(), 0);
}

IMediaBackend *ICore::getBackendForMimeType(QString mimeType)
{
    return m_instance->m_mediaBackends.value(mimeType, 0);
}


