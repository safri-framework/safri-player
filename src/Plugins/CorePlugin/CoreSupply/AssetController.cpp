#include "AssetController.h"
#include "../PluginSystem/pluginmanager.h"

using namespace Controller;
using namespace Core;

AssetController::AssetController(QObject *parent) :
    QObject(parent)
{
    PluginSystem::PluginManager* pluginManager = PluginSystem::PluginManager::instance();
    connect(pluginManager, SIGNAL(objectAdded(QObject*)), this, SLOT(objectAdded(QObject*)));
    QList<Core::IAssetService*> objects = PluginSystem::PluginManager::getObjects<Core::IAssetService>();

    for (int i = 0; i < objects.size(); i++)
    {
        addService( objects.at(i));
    }
}

QVariant AssetController::getAsset(QString serviceName, Core::DataItem *item)
{   
    Core::IAssetService* service;

    if ( item )
    {

        QMap<QString, IAssetService*>* tmp = assetServices.value(item->getType(), 0);
        if(tmp)
        {
            service = tmp->value(serviceName, 0);
            if(service)
            {
                return service->getAsset(item, serviceName);
            }
        }

        tmp = assetServices.value(DataItem::NONE);
        if(tmp)
        {
           service = tmp->value(serviceName, 0);
           if(service)
           {
               return service->getAsset(item, serviceName);
           }
        }

    }

    return QVariant();
}

void AssetController::objectAdded(QObject *object)
{
    Core::IAssetService* service = qobject_cast<Core::IAssetService*>(object);
    if(service)
    {
        addService(service);
    }
}

void AssetController::addService(IAssetService *service)
{
    DataItem::DATA_ITEM_TYPE type = service->getSupportedDataType();
    QMap<QString, IAssetService*>* map = assetServices.value(type, 0);
    if(map)
    {
        QStringList serviceList = service->getSupportedServices();
        for(int i = 0; i < serviceList.size(); i++)
        {
            map->insert(serviceList.at(i), service);
        }
    }
    else
    {
        QMap<QString, IAssetService*>* map = new QMap<QString, IAssetService*>();
        QStringList serviceList = service->getSupportedServices();
        for(int i = 0; i < serviceList.size(); i++)
        {
            map->insert(serviceList.at(i), service);
        }
        assetServices.insert(type, map);
    }
}
