#ifndef DARKBLUEPLAYERWIDGETPLUGIN_H
#define DARKBLUEPLAYERWIDGETPLUGIN_H

#include "darkblueplayerwidget_global.h"
#include "iplugin.h"

namespace Plugins
{
    class DARKBLUEPLAYERWIDGETSHARED_EXPORT DarkBluePlayerWidgetPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "DarkBluePlayerWidgetPlugin" FILE "darkblueplayerwidget.json")
        public:

            DarkBluePlayerWidgetPlugin();
            bool initialize(QStringList &arguments);
    };
}

#endif // DARKBLUEPLAYERWIDGETPLUGIN_H
