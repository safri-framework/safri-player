#ifndef TESTPLUGIN_H
#define TESTPLUGIN_H

#include "TestPlugin_global.h"
#include "iplugin.h"

class TESTPLUGINSHARED_EXPORT TestPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)
    public:

        TestPlugin();
        ~TestPlugin();

        bool initialize(QStringList &arguments);
};

#endif // TESTPLUGIN_H
