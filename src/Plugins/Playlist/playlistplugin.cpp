#include "playlistplugin.h"
#include "playlistfactory.h"

using namespace Plugins;

PlaylistPlugin::PlaylistPlugin()
{
}

bool PlaylistPlugin::initialize(QStringList &arguments)
{
    addObject(new PlaylistFactory() );
    return true;
}

Q_EXPORT_PLUGIN2(PlaylistPlugin, PlaylistPlugin)
