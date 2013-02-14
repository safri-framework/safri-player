#include <QtGui/QApplication>
#include <QDesktopServices>

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

    QString selectedPluginsFile = QDesktopServices::storageLocation(QDesktopServices::DataLocation);

#ifdef Q_OS_LINUX
    selectedPluginsFile.chop(2);
#endif

    selectedPluginsFile = selectedPluginsFile + "/.safri/selectedplugins.lst";

    PluginSystem::PluginManager manager("Safri.Core", paths, selectedPluginsFile);

    manager.loadPlugins();

    qDebug() << "Running main loop";

    return a.exec();
}
