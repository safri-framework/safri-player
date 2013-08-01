#ifndef SAFRI3SKINPLUGIN_H
#define SAFRI3SKINPLUGIN_H

#include "safri3skin_global.h"
#include "iplugin.h"

namespace Plugins
{
    class SAFRI3SKINSHARED_EXPORT Safri3SkinPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "Safri3SkinPlugin" FILE "safri3skin.json")
        public:

            Safri3SkinPlugin();
            bool initialize(QStringList &arguments);
    };
}

#endif // SAFRI2SKINPLUGIN_H
