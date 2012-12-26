#include "playlistwidgetplugin.h"
#include "playlistwidgetfactory.h"

using namespace Plugins;

PlaylistWidgetPlugin::PlaylistWidgetPlugin()
{
}

bool PlaylistWidgetPlugin::initialize(QStringList &arguments)
{
    addObject(new PlaylistWidgetFactory());
    return true;
}

Q_EXPORT_PLUGIN2(PlaylistWidgetPlugin, PlaylistWidgetPlugin)
