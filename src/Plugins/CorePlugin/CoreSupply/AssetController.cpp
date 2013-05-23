#include "AssetController.h"
#include "../PluginSystem/pluginmanager.h"

using namespace Controller;
AssetController::AssetController(QObject *parent) :
    QObject(parent)
{
    PluginSystem::PluginManager* pluginManager = PluginSystem::PluginManager::instance();
    connect(pluginManager, SIGNAL(objectAdded(QObject*)), this, SLOT(objectAdded(QObject*)));
    QList<Core::IAssetService*> objects = PluginSystem::PluginManager::getObjects<Core::IAssetService>();
    for (int i = 0; i < objects.size(); i++)
    {
        assetServices.insert(objects.at(i)->getName(), objects.at(i));
    }
}

QVariant AssetController::getAsset(QString serviceName, Core::DataItem *item)
{
    Core::IAssetService* service = assetServices.value(serviceName, 0);
    if(service)
    {
        return service->getAsset(item);
    }
    return QVariant();
}

void AssetController::objectAdded(QObject *object)
{
    Core::IAssetService* service = qobject_cast<Core::IAssetService*>(object);
    if(service)
    {
        assetServices.insert(service->getName(), service);
    }
}
