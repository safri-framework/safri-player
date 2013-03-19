#include "playlistplugin.h"
#include "playlistfactory.h"

using namespace Plugins;

PlaylistPlugin::PlaylistPlugin()
{
}

bool PlaylistPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    addObject(new PlaylistFactory() );
    return true;
}

