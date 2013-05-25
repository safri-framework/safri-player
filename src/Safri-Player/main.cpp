#include <QtWidgets/QApplication>
#include <QDesktopServices>

#include "pluginmanager.h"
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QUrl>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Safri-Player");

    qDebug() << "\n\nSafri-Player Version: " << SAFRI_VERSION << "\n\n";

    QStringList paths;
    paths << "plugins/";

    QString selectedPluginsFile =  QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);

    QDir dir(selectedPluginsFile);
    if(!dir.exists())
    {
        dir.mkpath(selectedPluginsFile);
    }

    selectedPluginsFile = selectedPluginsFile+("/selectedplugins.lst");
    qDebug()<<selectedPluginsFile;

    QFileInfo fileInfo(selectedPluginsFile);

    if (!fileInfo.exists())
    {

        qDebug()<<"Does not exist";
        qDebug()<<QFile::copy(":/defaults/selectedplugins.lst", selectedPluginsFile);
    }

    PluginSystem::PluginManager manager("Safri.Core", paths, selectedPluginsFile);

    manager.loadPlugins();

    qDebug() << "Running main loop";
    qDebug() <<   QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);

    return a.exec();
}
