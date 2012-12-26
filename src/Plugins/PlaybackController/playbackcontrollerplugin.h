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
        public:

            PlaybackControllerPlugin();
            ~PlaybackControllerPlugin();

            bool initialize(QStringList &arguments);
    };
}

#endif // PLAYBACKCONTROLLERPLUGIN_H
