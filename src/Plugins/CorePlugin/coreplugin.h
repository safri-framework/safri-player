#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include "CorePlugin_global.h"
#include "iplugin.h"

namespace Plugins
{
    class COREPLUGINSHARED_EXPORT CorePlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        public:

            CorePlugin();
            ~CorePlugin();

            bool initialize(QStringList &arguments);
    };
}
#endif // COREPLUGIN_H
