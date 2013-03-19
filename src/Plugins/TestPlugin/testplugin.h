#ifndef TESTPLUGIN_H
#define TESTPLUGIN_H

#include "TestPlugin_global.h"
#include "iplugin.h"

namespace Plugins
{
    class TESTPLUGINSHARED_EXPORT TestPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "TestPlugin" FILE "testplugin.json")

        public:

            TestPlugin();
            ~TestPlugin();

            bool initialize(QStringList &arguments);
    };
}

#endif // TESTPLUGIN_H
