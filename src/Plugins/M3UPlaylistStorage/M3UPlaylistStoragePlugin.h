#ifndef M3UPLAYLISTSTORAGEPLUGIN_H
#define M3UPLAYLISTSTORAGEPLUGIN_H

#include "M3UPlaylistStorage_global.h"

#include "iplugin.h"

namespace Plugins
{
    class M3UPLAYLISTSTORAGESHARED_EXPORT M3UPlaylistStoragePlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "M3UPlaylistStoragePlugin" FILE "M3UPlaylistStorage.json")

        public:

            M3UPlaylistStoragePlugin();

            bool initialize(QStringList &arguments);
    };
}

#endif // M3UPLAYLISTSTORAGEPLUGIN_H
