#ifndef SIDEBARPLUGINTESTPLUGIN_H
#define SIDEBARPLUGINTESTPLUGIN_H
#include "SidebarPluginTest_global.h"
#include "iplugin.h"

class SIDEBARPLUGINTESTSHARED_EXPORT SidebarPluginTestPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)

public:
    SidebarPluginTestPlugin();

    bool initialize(QStringList &arguments);
};

#endif // SIDEBARPLUGINTESTPLUGIN_H
