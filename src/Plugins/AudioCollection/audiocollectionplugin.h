#ifndef AUDIOCOLLECTIONPLUGIN_H
#define AUDIOCOLLECTIONPLUGIN_H

#include "AudioCollection_global.h"
#include "iplugin.h"

namespace Plugins
{
    class AUDIOCOLLECTIONSHARED_EXPORT AudioCollectionPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "AudioCollectionPlugin" FILE "audiocollectionplugin.json")

        public:

            AudioCollectionPlugin();
            bool initialize(QStringList &arguments);
    };
}

#endif // AUDIOCOLLECTIONPLUGIN_H
