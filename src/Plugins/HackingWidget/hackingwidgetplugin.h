#ifndef HACKINGWIDGETPLUGIN_H
#define HACKINGWIDGETPLUGIN_H

#include "HackingWidget_global.h"
#include "iplugin.h"

namespace Plugins
{
    class HACKINGWIDGETSHARED_EXPORT HackingWidgetPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "HackingWidgetPlugin" FILE "hackingwidget.json")

        public:

            HackingWidgetPlugin();

            bool initialize(QStringList &arguments);
    };
}

#endif // HACKINGWIDGETPLUGIN_H
