#ifndef SAFRIMOBILEGUIQML_H
#define SAFRIMOBILEGUIQML_H

#include "SafriApp_global.h"
#include "iplugin.h"

namespace Plugins
{
    class SAFRIAPPSHARED_EXPORT SafriAppPlugin: public PluginSystem::IPlugin{

        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "SafriApp" FILE "safriapp.json")

    public:

        SafriAppPlugin();
        bool initialize(QStringList &arguments);


    };
}

#endif // SAFRIMOBILEGUIQML_H
