#include "SongtreeWidgetPlugin.h"
#include "songtreesidebarwrapper.h"


SongtreeWidgetPlugin::SongtreeWidgetPlugin()
{
}

bool SongtreeWidgetPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    SongTreeSidebarWrapper* widget = new SongTreeSidebarWrapper();
    addObject(widget);
    return true;
}

