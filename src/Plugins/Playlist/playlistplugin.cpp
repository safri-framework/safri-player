#include "playlistplugin.h"


PlaylistPlugin::PlaylistPlugin()
{
}

bool PlaylistPlugin::initialize(QStringList &arguments)
{
    return true;
}

Q_EXPORT_PLUGIN2(PlaylistPlugin, PlaylistPlugin)
