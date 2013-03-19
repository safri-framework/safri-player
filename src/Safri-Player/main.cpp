#include <QtWidgets/QApplication>
#include <QDesktopServices>

#include "pluginmanager.h"
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //a.setApplicationName("Safri-Player");

    qDebug() << "\n\nSafri-Player Version: " << SAFRI_VERSION << "\n\n";

    QStringList paths;
    paths << "plugins/";

    QString selectedPluginsFile =  QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);
#ifdef Q_OS_LINUX
    selectedPluginsFile.chop(2);
#endif

    selectedPluginsFile = selectedPluginsFile+("/selectedplugins.lst");
    qDebug()<<selectedPluginsFile;

    QFileInfo fileInfo(selectedPluginsFile);

    if (!fileInfo.exists())
    {
        QFile::copy(":/defaults/selectedplugins.lst", selectedPluginsFile);
    }

    PluginSystem::PluginManager manager("Safri.Core", paths, selectedPluginsFile);

    manager.loadPlugins();

    qDebug() << "Running main loop";
    qDebug() <<   QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);

    return a.exec();
}
