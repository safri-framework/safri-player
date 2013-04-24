#ifndef TOUCHEVENTFILTERPLUGIN_H
#define TOUCHEVENTFILTERPLUGIN_H

#include "TouchEventFilterPlugin_global.h"
#include "iplugin.h"


namespace Plugins
{
    class TOUCHEVENTFILTERPLUGINSHARED_EXPORT TouchEventFilterPlugin: public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "TouchEventFilterPlugin" FILE "toucheventfilterplugin.json")

        public:

            TouchEventFilterPlugin();
            bool initialize(QStringList &arguments);
    };
}


#endif // TOUCHEVENTFILTERPLUGIN_H
