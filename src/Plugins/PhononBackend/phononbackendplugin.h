#ifndef PHONONBACKENDPLUGIN_H
#define PHONONBACKENDPLUGIN_H

#include "PhononBackend_global.h"
#include "iplugin.h"

class PHONONBACKENDSHARED_EXPORT PhononBackendPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)
    public:

        PhononBackendPlugin();
        ~PhononBackendPlugin();

        bool initialize(QStringList &arguments);
};

#endif // PHONONBACKENDPLUGIN_H
