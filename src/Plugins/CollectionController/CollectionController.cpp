#include "CollectionController.h"

#include "CoreData/DataItem.h"
#include "Interfaces/ICore.h"
#include "../PluginSystem/pluginmanager.h"
#include "Interfaces/IMediaCollectionStorageFactory.h"
#include "Interfaces/IMediaCollectionStorage.h"
#include "Interfaces/IMediaCollection.h"
#include <QStringList>
#include <QDebug>


Controller::CollectionController::CollectionController()
{
    // build list of storage factories
    QList<Core::IMediaCollectionStorageFactory*> objects = PluginSystem::PluginManager::getObjects<Core::IMediaCollectionStorageFactory>();
    int size = objects.size();

    for (int i = 0; i < size; i++)
    {
        m_storageFactories.insert(objects.at(i)->getStorageType(), objects.at(i));
    }

    loadExtensionMap();
}

QList<IMediaCollection *> Controller::CollectionController::getCollections(QString type)
{

    QList<IMediaCollection*> tempList;
    QList<IMediaCollection*> allCollections = m_collectionMap.values();

    for(int i = 0; i < allCollections.size(); i++)
    {
        if ( allCollections.at(i)->getContentType() == type )
        {
            tempList.append(allCollections.at(i));
        }
    }

    return tempList;
}

bool Controller::CollectionController::loadMediaCollection(QUrl filename)
{
    QString storageType = getStorageTypeByFilename(filename);
    Core::IMediaCollectionStorageFactory*   storageFactory = 0;
    Core::IMediaCollectionStorage*          collectionStorage = 0;
    Core::IMediaCollection*                 mediaCollection;


    storageFactory = m_storageFactories.value(storageType);

    if (storageFactory)
    {
        collectionStorage = storageFactory->createMediaCollectionStorage(filename);
        mediaCollection = collectionStorage->loadMediaCollection();

        if (mediaCollection)
        {
            m_collectionMap.insert(filename.toString(), mediaCollection);
            m_collectionHashMap.insert(mediaCollection->getHash(), mediaCollection);
            connect(mediaCollection, SIGNAL(itemAdded(Core::DataItem*)), this, SIGNAL(newItem(Core::DataItem*)));
            delete collectionStorage;
            return true;
        }

    }

    qDebug() << "could not load collection!";

    return false;
}

IMediaCollection *Controller::CollectionController::getMediaCollection(QUrl filename)
{
    if ( m_collectionMap.contains( filename.toString() ) )
    {
        return m_collectionMap.value( filename.toString() );
    }

    return 0;
}

IMediaCollection *Controller::CollectionController::getMediaCollectionByHash(QString hash)
{
    if ( m_collectionHashMap.contains( hash ) )
    {
        return m_collectionHashMap.value( hash );
    }

    return 0;
}

bool Controller::CollectionController::saveCollections()
{
    bool result = true;
    qDebug() << "CollectionController::saveCollections()";

    QList<IMediaCollection*> allCollections = m_collectionMap.values();
    Core::IMediaCollectionStorageFactory*   storageFactory = 0;
    Core::IMediaCollectionStorage*          collectionStorage = 0;

    for(int i = 0; i < allCollections.size(); i++)
    {
        storageFactory = m_storageFactories.value( getStorageTypeByFilename( allCollections.at(i)->getDatabaseLocation() ) );

        if (storageFactory)
        {
            collectionStorage = storageFactory->createMediaCollectionStorage( allCollections.at(i)->getDatabaseLocation() );
            collectionStorage->saveMediaCollection(allCollections.at(i));

            delete collectionStorage;
        }
    }

    return result;
}

Media *Controller::CollectionController::findMediaByURL(QUrl& filename)
{
    QList<IMediaCollection*> allCollections = m_collectionMap.values();
    Media* foundMedia = 0;

    for (int i = 0; i < allCollections.size(); i++)
    {
        //qDebug() << "findMediaByURL: " << filename;
        foundMedia = allCollections.at(i)->getMediaByURL(filename);

        if (foundMedia)
        {
            // returns the first found media
            return foundMedia;
        }
    }

    return foundMedia;
}

void Controller::CollectionController::loadExtensionMap()
{
    m_fileExtensionMap.insert("db","org.safri.sqlite.audio");
}

QString Controller::CollectionController::getStorageTypeByFilename(QUrl filename)
{
    QStringList tmp = filename.toString().split(".");
    QString extension = tmp.last();

    if ( m_fileExtensionMap.contains( extension ) )
    {
        return m_fileExtensionMap.value( extension );
    }

    qDebug()<<"Unknown File Type";
    return "";
}


void Controller::CollectionController::objectAddedToObjectPool(QObject *object)
{
    Q_UNUSED(object)
}
