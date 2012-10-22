#include "playlistplugin.h"
#include "playlistfactory.h"

PlaylistPlugin::PlaylistPlugin()
{
}

bool PlaylistPlugin::initialize(QStringList &arguments)
{
    addObject(new PlaylistFactory() );
    return true;
}

Q_EXPORT_PLUGIN2(PlaylistPlugin, PlaylistPlugin)
