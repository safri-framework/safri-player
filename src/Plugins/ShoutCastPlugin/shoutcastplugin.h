#ifndef SHOUTCASTPLUGIN_H
#define SHOUTCASTPLUGIN_H

#include "ShoutCastPlugin_global.h"
#include "iplugin.h"

namespace Plugins
{
    class SHOUTCASTPLUGINSHARED_EXPORT ShoutCastPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
    Q_PLUGIN_METADATA(IID "ShoutCastPlugin" FILE "shoutcastplugin.json")
        public:
            ShoutCastPlugin();
            bool initialize(QStringList &arguments);
    };
}

#endif // SHOUTCASTPLUGIN_H
