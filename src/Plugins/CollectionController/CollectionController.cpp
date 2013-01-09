#include "CollectionController.h"
#include "../Plugins/CorePlugin/icore.h"
#include "../Plugins/CorePlugin/Interfaces/IStorageAdapter.h"
#include "../PluginSystem/pluginmanager.h"
#include <QStringList>
#include <QDebug>


Controller::CollectionController::CollectionController()
{

    QList<Core::IStorageAdapterFactory*> objects = PluginSystem::PluginManager::instance()->getObjects<Core::IStorageAdapterFactory>();
    for (int i = 0; i < objects.size(); i++)
    {
        m_factoryMap.insert(objects.at(i)->getStorageType(), objects.at(i));
    }



    QList<Core::IMediaCollectionBuilder*> builderList = PluginSystem::PluginManager::instance()->getObjects<Core::IMediaCollectionBuilder>();
    for(int i = 0; i < builderList.size(); i++)
    {
        m_builderMap.insert(builderList.at(i)->getCollectionType(), builderList.at(i));
    }

    loadExtensionMap();


}

QList<IMediaCollection *> Controller::CollectionController::getCollections(QString type)
{
    QList<IMediaCollection*> tempList;
    QList<IMediaCollection*> allCollections = m_collectionMap.values();
    for(int i = 0; i < allCollections.size(); i++)
    {
        if(allCollections.at(i)->getContentType() == type)
            tempList.append(allCollections.at(i));
    }
    return tempList;
}

bool Controller::CollectionController::loadMediaCollection(QUrl filename)
{

    Core::IStorageAdapter * storageAdapter = 0;
    IStorageAdapterFactory* storageFactory = 0;

    QString storageType = getStorageTypeByFilename(filename.toString());
    storageFactory = m_factoryMap.value(storageType);
    Q_ASSERT (storageFactory !=0);
    storageAdapter = storageFactory->createStorageAdapter(filename);
    if(storageFactory)
    {
          QString contentType = storageAdapter->getContentType();

          IMediaCollectionBuilder* audioBuilder = m_builderMap.value(contentType);
          IMediaCollection* collection = audioBuilder->buildMediaCollection(storageAdapter);
          m_collectionMap.insert(filename.toString(), collection);
          return true;

    }
    else
    {
        qDebug()<<"Datenbank konnte nicht geladen werden.";
        return false;
    }
}

IMediaCollection *Controller::CollectionController::getMediaCollection(QUrl filename)
{
    if(m_collectionMap.contains(filename.toString()))
    {
        return m_collectionMap.value(filename.toString());
    }
    else
    {
        return 0;
    }
}

void Controller::CollectionController::loadExtensionMap()
{
    m_fileExtensionMap.insert(".db","org.safri.sqlite");
}

QString Controller::CollectionController::getStorageTypeByFilename(QString filename)
{
    QStringList tmp = filename.split(".");
    QString extension = tmp.last();

    if(m_fileExtensionMap.contains(extension))
    {
        return m_fileExtensionMap.value(extension);
    }
    else
    {
        qDebug()<<"Unknown File Type";
        return "";
    }
}




void Controller::CollectionController::objectAddedToObjectPool(QObject *object)
{
}
