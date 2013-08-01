#ifndef DARKBLUESKINPLUGIN_H
#define DARKBLUESKINPLUGIN_H

#include "darkblueskin_global.h"
#include "iplugin.h"

namespace Plugins
{
    class DARKBLUESKINSHARED_EXPORT DarkBlueSkinPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "DarkBlueSkinPlugin" FILE "darkblueskin.json")
        public:

            DarkBlueSkinPlugin();
            bool initialize(QStringList &arguments);
    };
}

#endif // DARKBLUESKINPLUGIN_H
