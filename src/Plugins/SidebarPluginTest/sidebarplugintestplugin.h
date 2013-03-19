#ifndef SIDEBARPLUGINTESTPLUGIN_H
#define SIDEBARPLUGINTESTPLUGIN_H

#include "SidebarPluginTest_global.h"
#include "iplugin.h"

namespace Plugins
{
    class SIDEBARPLUGINTESTSHARED_EXPORT SidebarPluginTestPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
    Q_PLUGIN_METADATA(IID "SidebarPluginTestPlugin" FILE "sidebarplugintest.json")
        public:
            SidebarPluginTestPlugin();

            bool initialize(QStringList &arguments);
    };
}

#endif // SIDEBARPLUGINTESTPLUGIN_H


