#ifndef SAFRI2SKINPLUGIN_H
#define SAFRI2SKINPLUGIN_H

#include "safri2skin_global.h"
#include "iplugin.h"

namespace Plugins
{
    class SAFRI2SKINSHARED_EXPORT Safri2SkinPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "Safri2SkinPlugin" FILE "safri2skin.json")
        public:

            Safri2SkinPlugin();
            bool initialize(QStringList &arguments);
    };
}

#endif // SAFRI2SKINPLUGIN_H
