#ifndef MAINWINDOWPLUGIN_H
#define MAINWINDOWPLUGIN_H

#include "iplugin.h"
#include "MainWindow_global.h"
#include "mainwindow.h"

class MAINWINDOWSHARED_EXPORT MainWindowPlugin : public PluginSystem::IPlugin
{

    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)

public:
    bool initialize(QStringList &arguments);
    MainWindowPlugin();

};

#endif // MAINWINDOW_H
