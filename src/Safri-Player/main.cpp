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
#include <QProxyStyle>

class Style_tweaks : public QProxyStyle
{
    public:

        void drawItemText(QPainter *painter, const QRect &rect, int flags, const QPalette &pal, bool enabled, const QString &text, QPalette::ColorRole textRole) const
        {
            QProxyStyle::drawItemText(painter, rect, flags, pal, enabled, text);
        }
        void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
        {
            /* do not draw focus rectangles - this permits modern styling */
            if (element == QStyle::PE_FrameFocusRect)
                return;
            QProxyStyle::drawPrimitive(element, option, painter, widget);
        }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Safri-Player");

    QPalette palette = a.palette();

    //ui->pLabel->setPalette(palette);
    palette.setColor(QPalette::ButtonText, QColor("#DFDFDF"));
    palette.setColor(QPalette::Text, QColor("#DFDFDF"));
    palette.setColor(QPalette::WindowText, QColor("#DFDFDF"));
    a.setPalette(palette);
    a.setStyle(new Style_tweaks());

    qDebug() << "\n\nSafri-Player Version: " << SAFRI_VERSION << "";

    qDebug() << QString::number(argc);

    QStringList paths;
    QString selectedPluginsFile;
    QString storageDirectory;


#if defined SAFRI_PORTABLE && ! defined ANDROID
    storageDirectory = QCoreApplication::applicationDirPath() + "/profile";
#else
    storageDirectory = QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);
#endif

    QString configFilename = storageDirectory + "/safri-config.xml";

#ifdef ANDROID


    qDebug() << "Android build...";

    selectedPluginsFile = "assets:/" + QString(SELECTED_PLUGINS_FILE);
    paths << "assets:/plugins";

    // copy config file
    QDir dir(storageDirectory);
    if (!dir.exists())
    {
        dir.mkpath(storageDirectory);
    }

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

    if (selectedPluginsFile.isEmpty())
    {
        selectedPluginsFile = storageDirectory + "/" + QString(SELECTED_PLUGINS_FILE);
    }
    else if (!selectedPluginsFile.contains("/"))
    {
        // if the command line argument contains no path, use the default location
        selectedPluginsFile = storageDirectory + "/" + selectedPluginsFile;
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

    QFileInfo configInfo(configFilename);
    if (!configInfo.exists())
    {
        qDebug() << "Copying default safri-config.xml";
        qDebug() << QFile::copy(":/defaults/safri-config.xml", configFilename);

        QFile::setPermissions(configFilename, QFileDevice::WriteUser | QFileDevice::ReadUser);
    }

    qDebug() << "\n\n";

    PluginSystem::PluginManager manager("Safri.Core", paths, selectedPluginsFile);

    manager.loadPlugins();

    qDebug() << "Running main loop";
    return a.exec();
}
