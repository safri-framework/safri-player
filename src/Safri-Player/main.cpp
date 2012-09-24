#include <QtCore/QCoreApplication>

#include "pluginmanager.h"
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "\n\nSafri-Player Version: " << SAFRI_VERSION << "\n\n";

    QStringList paths;
    paths << "plugins/";

    PluginSystem::PluginManager manager(paths);

    manager.loadPlugins();

    return a.exec();
}
