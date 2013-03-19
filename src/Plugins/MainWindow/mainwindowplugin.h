#ifndef MAINWINDOWPLUGIN_H
#define MAINWINDOWPLUGIN_H

#include "iplugin.h"
#include "MainWindow_global.h"
#include "mainwindow.h"

namespace Plugins
{
    class MAINWINDOWSHARED_EXPORT MainWindowPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "MainWindow" FILE "mainwindow.json")
        public:

            bool initialize(QStringList &arguments);
            MainWindowPlugin();
    };
}

#endif // MAINWINDOW_H
