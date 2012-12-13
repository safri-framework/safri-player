#include "mainwindowplugin.h"


bool MainWindowPlugin::initialize(QStringList &arguments)
{
    MainWindow* window = new MainWindow();
    window->show();
    return true;
}

MainWindowPlugin::MainWindowPlugin()
{
}

Q_EXPORT_PLUGIN2(MainWindowPlugin, MainWindowPlugin)
