#ifndef COLLECTIONCONTROLLERPLUGIN_H
#define COLLECTIONCONTROLLERPLUGIN_H
#include "CollectionController_global.h"
#include "../PluginSystem/iplugin.h"


class COLLECTIONCONTROLLERSHARED_EXPORT CollectionControllerPlugin : public PluginSystem::IPlugin
{
    Q_PLUGIN_METADATA(IID "CollectionControllerPlugin" FILE "collectioncontroller.json")
public:
    CollectionControllerPlugin();
    bool initialize(QStringList &arguments);


};


#endif // COLLECTIONCONTROLLERPLUGIN_H
