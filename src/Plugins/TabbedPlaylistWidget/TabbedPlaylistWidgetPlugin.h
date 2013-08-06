#ifndef TABBEDPLAYLISTWIDGETPLUGIN_H
#define TABBEDPLAYLISTWIDGETPLUGIN_H

#include "tabbedplaylistwidget_global.h"
#include "iplugin.h"

class TABBEDPLAYLISTWIDGETSHARED_EXPORT TabbedPlaylistWidgetPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)
    Q_PLUGIN_METADATA(IID "TabbedPlaylistWidgetPlugin" FILE "TabbedPlaylistWidget.json")
    public:

        TabbedPlaylistWidgetPlugin();

        bool initialize(QStringList &arguments);
};

#endif // TABBEDPLAYLISTWIDGETPLUGIN_H
