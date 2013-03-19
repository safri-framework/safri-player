#ifndef PLAYERWIDGETPLUGIN_H
#define PLAYERWIDGETPLUGIN_H

#include "PlayerWidget_global.h"
#include "iplugin.h"

namespace Plugins
{
    class PLAYERWIDGETSHARED_EXPORT PlayerWidgetPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "PlayerWidgetPlugin" FILE "playerwidget.json")

        public:

            PlayerWidgetPlugin();
            bool initialize(QStringList &arguments);
    };
}

#endif // PLAYERWIDGETPLUGIN_H
