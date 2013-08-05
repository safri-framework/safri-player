#include "mainwindowplugin.h"

using namespace Plugins;

bool MainWindowPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    MainWindow* window = new MainWindow();
    window->show();
    addObject(window);
    return true;
}

MainWindowPlugin::MainWindowPlugin()
{
}


