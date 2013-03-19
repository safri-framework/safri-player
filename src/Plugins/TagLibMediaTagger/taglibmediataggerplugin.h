#ifndef TAGLIBMEDIATAGGERPLUGIN_H
#define TAGLIBMEDIATAGGERPLUGIN_H

#include "TagLibMediaTagger_global.h"
#include "iplugin.h"

namespace Plugins
{
    class TAGLIBMEDIATAGGERSHARED_EXPORT TagLibMediaTaggerPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "TagLibMediaTaggerPlugin" FILE "taglibmediatagger.json")

        public:

            TagLibMediaTaggerPlugin();
            bool initialize(QStringList &arguments);
    };
}

#endif // TAGLIBMEDIATAGGERPLUGIN_H
