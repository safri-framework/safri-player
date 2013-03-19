#ifndef PLAYBACKCONTROLLERPLUGIN_H
#define PLAYBACKCONTROLLERPLUGIN_H

#include "PlaybackController_global.h"
#include "iplugin.h"

namespace Plugins
{
    class PLAYBACKCONTROLLERSHARED_EXPORT PlaybackControllerPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "PlaybackControllerPlugin" FILE "playbackcontroller.json")

        public:

            PlaybackControllerPlugin();
            ~PlaybackControllerPlugin();

            bool initialize(QStringList &arguments);
    };
}

#endif // PLAYBACKCONTROLLERPLUGIN_H
