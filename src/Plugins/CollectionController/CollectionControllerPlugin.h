#ifndef COLLECTIONCONTROLLERPLUGIN_H
#define COLLECTIONCONTROLLERPLUGIN_H
#include "CollectionController_global.h"
#include "../PluginSystem/iplugin.h"


class COLLECTIONCONTROLLERSHARED_EXPORT CollectionControllerPlugin : public PluginSystem::IPlugin
{
public:
    CollectionControllerPlugin();
    bool initialize(QStringList &arguments);

};

Q_EXPORT_PLUGIN2(CollectionControllerPlugin, CollectionControllerPlugin)
#endif // COLLECTIONCONTROLLERPLUGIN_H
