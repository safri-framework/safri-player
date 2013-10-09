#ifndef PROGRESSSIDEBARWIDGET_H
#define PROGRESSSIDEBARWIDGET_H

#include "progresssidebarwidget_global.h"
#include "iplugin.h"

class PROGRESSSIDEBARWIDGETSHARED_EXPORT ProgressSidebarWidgetPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)
    Q_PLUGIN_METADATA(IID "ProgressSidebarWidgetPlugin" FILE "ProgressSidebarWidget.json")
    public:
        ProgressSidebarWidgetPlugin();

        bool initialize(QStringList &arguments);
};

#endif // PROGRESSSIDEBARWIDGET_H
