#include "infocontroller.h"
#include "pluginmanager.h"
#include "Interfaces/IInfoResolver.h"
#include <QStringList>

using namespace Controller;
using namespace Core;

InfoController::InfoController(QObject *parent) :
    QObject(parent)
{
    // build list of resolver
    QList<IInfoResolver*> objects = PluginSystem::PluginManager::getObjects<IInfoResolver>();
    int resolverCount = objects.size();
    int typeCount;
    QStringList infoTypes;

    for (int i = 0; i < resolverCount; i++)
    {
        infoTypes = objects.at(i)->getSupportedInfoTypes();

        typeCount = infoTypes.size();

        for (int j = 0; j < typeCount; j++)
        {
            resolver.insertMulti(infoTypes.at(j), objects.at(i));
        }
    }

    connect(PluginSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)), this, SLOT(objectAddedToObjectPool(QObject*)));
}

InfoRequest *InfoController::getInfoForItem(QString type, Core::DataItem *item)
{
    IInfoResolver* respondenResolver = resolver.value(type);

    if (respondenResolver != 0)
    {
        return respondenResolver->getInfoForItem(type, item);
    }

    return 0;
}

void InfoController::objectAddedToObjectPool(QObject *object)
{
    IInfoResolver* newResolver = qobject_cast<IInfoResolver*>(object);
    int typeCount;
    QStringList infoTypes;

    if (newResolver != 0)
    {
        infoTypes = newResolver->getSupportedInfoTypes();

        typeCount = infoTypes.size();

        for (int i = 0; i < typeCount; i++)
        {
            resolver.insertMulti(infoTypes.at(i), newResolver);
        }
    }
}
