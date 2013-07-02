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

    qDebug() << QString::number(argc);

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

    QString argument;

    for (int i = 1; i < argc; i++)
    {
        argument = QString(argv[i]);

        if (argument == "--plugins-file")
        {
            i++;
            selectedPluginsFile = QString(argv[i]);
        }
    }

    /*
    selectedPluginsFile =  ;
    QDir dir(selectedPluginsFile);
    if(!dir.exists())
    {
        dir.mkpath(selectedPluginsFile);
    }

    selectedPluginsFile = selectedPluginsFile + "/" + QString(SELECTED_PLUGINS_FILE);
    qDebug()<<selectedPluginsFile;
    */

    if (selectedPluginsFile.isEmpty())
    {
        selectedPluginsFile = QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0) + "/" + QString(SELECTED_PLUGINS_FILE);
    }
    else if (!selectedPluginsFile.contains("/"))
    {
        // if the command line argument contains no path, use the default location
        selectedPluginsFile = QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0) + "/" + selectedPluginsFile;
    }

    QString absolutePath = QFileInfo(selectedPluginsFile).absolutePath();
    QDir dir(absolutePath);
    if(!dir.exists())
    {
        dir.mkpath(absolutePath);
    }

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
