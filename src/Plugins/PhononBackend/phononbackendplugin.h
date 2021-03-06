#ifndef PHONONBACKENDPLUGIN_H
#define PHONONBACKENDPLUGIN_H

#include "PhononBackend_global.h"
#include "iplugin.h"

namespace Plugins
{
    class PHONONBACKENDSHARED_EXPORT PhononBackendPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "PhononBackendPlugin" FILE "phononbackend.json")

        public:

            PhononBackendPlugin();
            ~PhononBackendPlugin();

            bool initialize(QStringList &arguments);
    };
}

#endif // PHONONBACKENDPLUGIN_H
