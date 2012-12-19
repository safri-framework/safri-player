#ifndef PLAYLISTWIDGETPLUGIN_H
#define PLAYLISTWIDGETPLUGIN_H

#include "iplugin.h"
#include "PlaylistWidget_global.h"

class PLAYLISTWIDGETSHARED_EXPORT PlaylistWidgetPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)
    public:

        PlaylistWidgetPlugin();

        bool initialize(QStringList &arguments);
};

#endif // PLAYLISTWIDGETPLUGIN_H
