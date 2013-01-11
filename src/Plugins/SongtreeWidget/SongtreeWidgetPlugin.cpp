#include "SongtreeWidgetPlugin.h"
#include "songtreesidebarwrapper.h"


SongtreeWidgetPlugin::SongtreeWidgetPlugin()
{
}

bool SongtreeWidgetPlugin::initialize(QStringList &arguments)
{
    SongTreeSidebarWrapper* widget = new SongTreeSidebarWrapper();
    addObject(widget);
    return true;
}

Q_EXPORT_PLUGIN2(SongtreeWidgetPlugin, SongtreeWidgetPlugin)
