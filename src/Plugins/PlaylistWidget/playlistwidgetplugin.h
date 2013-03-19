#ifndef PLAYLISTWIDGETPLUGIN_H
#define PLAYLISTWIDGETPLUGIN_H

#include "iplugin.h"
#include "PlaylistWidget_global.h"

namespace Plugins
{
    class PLAYLISTWIDGETSHARED_EXPORT PlaylistWidgetPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "PlaylistWidgetPlugin" FILE "playlistwidget.json")

        public:

            PlaylistWidgetPlugin();

            bool initialize(QStringList &arguments);
    };
}

#endif // PLAYLISTWIDGETPLUGIN_H
