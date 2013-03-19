#ifndef SONGTREEWIDGETPLUGIN_H
#define SONGTREEWIDGETPLUGIN_H
#include "SongtreeWidget_global.h"
#include "iplugin.h"

class SONGTREEWIDGETSHARED_EXPORT SongtreeWidgetPlugin: public PluginSystem::IPlugin
{

    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)
    Q_PLUGIN_METADATA(IID "SongTreeWidgetPlugin" FILE "songtreewidget.json")


public:
    SongtreeWidgetPlugin();
    bool initialize(QStringList &arguments);


};

#endif // SONGTREEWIDGETPLUGIN_H
