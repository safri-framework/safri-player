#ifndef SAFRIMPCPLUGIN_H
#define SAFRIMPCPLUGIN_H

#include "safrimpc_global.h"
#include "iplugin.h"



namespace Plugins
{
    class SAFRIMPCSHARED_EXPORT SafriMPC : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "SafriMPCPlugin" FILE "safrimpc.json")
    public:
        SafriMPC();
        bool initialize(QStringList &arguments);
    };
}

#endif // SAFRIMPCPLUGIN_H
