#include "shoutcastplugin.h"
#include "shoutcastsidebar.h"



Plugins::ShoutCastPlugin::ShoutCastPlugin()
{

}

bool Plugins::ShoutCastPlugin::initialize(QStringList &arguments)
{
    ShoutCastSideBar* shoutCast = new ShoutCastSideBar();
    addObject(shoutCast);
    return true;
}
