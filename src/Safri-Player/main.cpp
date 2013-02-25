#include <QtGui/QApplication>
#include <QDesktopServices>

#include "pluginmanager.h"
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //a.setApplicationName("Safri-Player");

    qDebug() << "\n\nSafri-Player Version: " << SAFRI_VERSION << "\n\n";

    QStringList paths;
    paths << "plugins/";

    QString selectedPluginsFile = QDesktopServices::storageLocation(QDesktopServices::DataLocation);

#ifdef Q_OS_LINUX
    selectedPluginsFile.chop(2);
#endif

    selectedPluginsFile = selectedPluginsFile + "/.safri/selectedplugins.lst";

    QFileInfo fileInfo(selectedPluginsFile);

    if (!fileInfo.exists())
    {
        QFile::copy(":/defaults/selectedplugins.lst", selectedPluginsFile);
    }

    PluginSystem::PluginManager manager("Safri.Core", paths, selectedPluginsFile);

    manager.loadPlugins();

    qDebug() << "Running main loop";

    return a.exec();
}
