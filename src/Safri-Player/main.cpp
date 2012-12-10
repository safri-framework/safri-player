#include <QtGui/QApplication>

#include "pluginmanager.h"
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "\n\nSafri-Player Version: " << SAFRI_VERSION << "\n\n";

    QStringList paths;
    paths << "plugins/";

    PluginSystem::PluginManager manager("Core", paths);

    manager.loadPlugins();

    return a.exec();
}
