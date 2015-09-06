#include "sidebarplugintestplugin.h"
#include "sidebarplugintest.h"

using namespace Plugins;

SidebarPluginTestPlugin::SidebarPluginTestPlugin()
{
}

bool SidebarPluginTestPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    SidebarPluginTest* plugin1 = new SidebarPluginTest("Oans");
    SidebarPluginTest* plugin2 = new SidebarPluginTest("Zwoa");
    SidebarPluginTest* plugin3 = new SidebarPluginTest("Drei");
    addObject(plugin1);
    addObject(plugin2);
    addObject(plugin3);
    return true;

}


