#ifndef PLAYLISTPLUGIN_H
#define PLAYLISTPLUGIN_H

#include "Playlist_global.h"
#include "iplugin.h"
class PLAYLISTSHARED_EXPORT PlaylistPlugin:public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)


public:
    PlaylistPlugin();
    bool initialize(QStringList &arguments);

};

#endif // PLAYLISTPLUGIN_H
