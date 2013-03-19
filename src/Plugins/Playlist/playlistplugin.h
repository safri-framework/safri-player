#ifndef PLAYLISTPLUGIN_H
#define PLAYLISTPLUGIN_H

#include "Playlist_global.h"
#include "iplugin.h"

namespace Plugins
{
    class PLAYLISTSHARED_EXPORT PlaylistPlugin:public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "PlaylistPlugin" FILE "playlistplugin.json")

        public:

            PlaylistPlugin();
            bool initialize(QStringList &arguments);
    };
}

#endif // PLAYLISTPLUGIN_H
