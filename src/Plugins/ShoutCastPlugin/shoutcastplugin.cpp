#include "shoutcastplugin.h"
#include "shoutcastsidebar.h"



Plugins::ShoutCastPlugin::ShoutCastPlugin()
{

}

bool Plugins::ShoutCastPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    ShoutCastSideBar* shoutCast = new ShoutCastSideBar();
    addObject(shoutCast);
    return true;
}
