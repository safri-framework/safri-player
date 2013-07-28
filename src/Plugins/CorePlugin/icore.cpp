#include "icore.h"
#include "pluginmanager.h"
#include "iplaybackcontroller.h"
#include "Interfaces/IMediaBackend.h"
#include "Interfaces/IPlaylistFactory.h"
#include "Interfaces/iguicontroller.h"
#include "Interfaces/ICollectionController.h"
#include "Interfaces/imediacollectionfactory.h"
#include "CoreData/media.h"
#include "CoreSupply/infocontroller.h"
#include "CoreSupply/AssetController.h"
#include "Settings/SettingsManager.h"

#include <QDebug>
#include <QDesktopServices>
#include <QStandardPaths>
#include "Settings/SettingsManagerDialog.h"
#include <QUrl>

using namespace Core;

ICore* ICore::m_instance = 0;

ICore::ICore()
    : m_playbackController(0), m_audioBackend(0), m_playlistFactory(0), m_guiController(0), m_collectionController(0)
{
    qDebug() << "ICore()";
    connect(PluginSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)), this, SLOT(objectAddedToObjectPool(QObject*)));
    m_infoController = new Controller::InfoController(this);
    m_assetController = new Controller::AssetController(this);
    PluginSystem::PluginManager::instance()->addObject(m_assetController);
    m_settingsManager = SettingsManager::getInstance();
}

ICore *ICore::instance()
{
    return m_instance;
}

Controller::InfoController *ICore::infoController()
{
    return m_instance->m_infoController;
}

SettingsManager *ICore::settingsManager()
{
    return m_instance->m_settingsManager;
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
        return;
    }

    IMediaBackend *media_backend = qobject_cast<IMediaBackend*>(object);
    if (media_backend != 0)
    {
        qDebug() << "IMediaBackend class added";
        m_audioBackend = media_backend;

        QStringList mimeTypes = media_backend->getSupportedMimeTypes();
        for (int i = 0; i < mimeTypes.size(); i++)
        {
            qDebug() << "Added MediaBackend for MimeType: " << mimeTypes.at(i);
            m_mediaBackends.insertMulti(mimeTypes.at(i), media_backend);
        }
        return;
    }

    IPlaylistFactory *playlistFactory = qobject_cast<IPlaylistFactory*>(object);
    if (playlistFactory != 0)
    {
        m_playlistFactory = playlistFactory;
        return;
    }

    IGUIController *guiController = qobject_cast<IGUIController*>(object);
    if (guiController != 0)
    {
        qDebug() << "ICore::IGUIController class added";
        m_guiController = guiController;
        return;
    }

    ICollectionController *collectionController = qobject_cast<ICollectionController*>(object);
    if (collectionController != 0)
    {
        qDebug() << "ICore::ICollectionController class added";
        m_collectionController = collectionController;
        return;
    }

    IMediaCollectionFactory *collectionFactory = qobject_cast<IMediaCollectionFactory*>(object);
    if (collectionFactory != 0)
    {
        qDebug() << "Core::IMediaCollectionFactory class added";
        m_collectionFactories.insert(collectionFactory->getCollectionType(), collectionFactory);
        return;
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
    QString storageLocation = QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);
    return  storageLocation;
}

IMediaBackend *ICore::getBackendForMedia(Media *media)
{
    if (media)
    {
        qDebug()<<Q_FUNC_INFO<<media->getMimeType();
        return m_instance->m_mediaBackends.value(media->getMimeType(), 0);
    }
    else
    {
        return 0;
    }
}

IMediaBackend *ICore::getBackendForMimeType(QString mimeType)
{
    return m_instance->m_mediaBackends.value(mimeType, 0);
}

IMediaCollection *ICore::createMediaCollection(QString type, QString collectionName, QUrl url)
{
    IMediaCollectionFactory* factory = m_instance->m_collectionFactories.value(type);
    if (factory != 0)
    {
            return factory->createMediaCollection(collectionName, url);
    }

    return 0;
}

Controller::AssetController *ICore::assetController()
{
    return m_assetController;
}

void ICore::showSettingsDialog()
{
    SettingsManagerDialog dialog(ICore::settingsManager());

    if ( dialog.exec() == QDialog::Accepted )
    {
        dialog.saveSettings();
    }
}


