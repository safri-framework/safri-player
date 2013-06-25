#include <QtWidgets/QApplication>
#include <QDesktopServices>

#include "pluginmanager.h"
#include <QPluginLoader>
#include <QStringList>
#include <QDirIterator>
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QUrl>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Safri-Player");

    qDebug() << "\n\nSafri-Player Version: " << SAFRI_VERSION << "";

    QStringList paths;
    QString selectedPluginsFile;

#ifdef ANDROID


    qDebug() << "Android build...";

    selectedPluginsFile = "assets:/" + QString(SELECTED_PLUGINS_FILE);
    paths << "assets:/plugins";

    /*
    QFile file;

    file.setFileName("assets:/selectedplugins.lst");
    file.open(QFile::ReadOnly);
    QString text = QLatin1String(file.readAll());
    file.close();

    qDebug() << "Selected: " << text;
    */

    /*
    QStringList pluginSpecNameFilters;
    pluginSpecNameFilters.append("*.xml");
    QString filename;

    QDir dir("assets:/plugins");
    dir.setNameFilters(pluginSpecNameFilters);
    QDirIterator dirIterator(dir, QDirIterator::Subdirectories);

    while (dirIterator.hasNext())
    {
        dirIterator.next();
        filename = dirIterator.fileInfo().absoluteFilePath();

        qDebug() << "file: " << filename;
    }
    */


#else

    qDebug() << "Non-android build";

    paths << "plugins/";

    selectedPluginsFile =  QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);
    QDir dir(selectedPluginsFile);
    if(!dir.exists())
    {
        dir.mkpath(selectedPluginsFile);
    }

    selectedPluginsFile = selectedPluginsFile + "/" + QString(SELECTED_PLUGINS_FILE);
    qDebug()<<selectedPluginsFile;

    QFileInfo fileInfo(selectedPluginsFile);

    if (!fileInfo.exists())
    {
        qDebug() << "Copying default selectedplugins.lst";
        qDebug() << QFile::copy(":/defaults/" + QString(SELECTED_PLUGINS_FILE), selectedPluginsFile);
    }

#endif

    qDebug() << "\n\n";


    PluginSystem::PluginManager manager("Safri.Core", paths, selectedPluginsFile);

    manager.loadPlugins();

    qDebug() << "Running main loop";
    return a.exec();


/*

selectedPluginsFile =  QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);

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
*/
}
