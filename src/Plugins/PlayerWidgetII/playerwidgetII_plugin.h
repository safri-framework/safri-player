#ifndef PLAYERWIDGETII_H
#define PLAYERWIDGETII_H

#include "PlayerWidgetII_global.h"
#include "iplugin.h"

namespace Plugins
{
    class PLAYERWIDGETIISHARED_EXPORT PlayerWidgetII_Plugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
         Q_PLUGIN_METADATA(IID "PlayerWidgetPluginII" FILE "playerwidgetII.json")
    public:
        PlayerWidgetII_Plugin();
        bool initialize(QStringList &arguments);
    };
}
#endif // PLAYERWIDGETII_H
