#include "playlistwidgetplugin.h"
#include "playlistwidgetfactory.h"

using namespace Plugins;

PlaylistWidgetPlugin::PlaylistWidgetPlugin()
{
}

bool PlaylistWidgetPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    addObject(new PlaylistWidgetFactory());
    return true;
}


