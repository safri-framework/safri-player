#include "pluginmanager.h"
#include "pluginspec.h"
#include "pluginviewer.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QPluginLoader>
#include <QTextStream>

using namespace PluginSystem;

PluginManager *PluginManager::m_instance = 0;

PluginManager::PluginManager(QString corePluginName, QStringList pluginPaths, QString selectedPluginsFile)
    : QObject(0), pluginPaths(pluginPaths), corePluginName(corePluginName), selectedPluginsFile(selectedPluginsFile)
{
    qDebug() << "PluginManager(QStringList pluginPaths)";
    m_instance = this;
}

PluginManager *PluginManager::instance()
{
    return m_instance;
}

void PluginManager::addObject(QObject *object)
{
    objectPool.append(object);
    Q_EMIT objectAdded(object);
}

void PluginManager::removeObject(QObject *object)
{
    Q_EMIT objectAboutToRemove(object);
    objectPool.removeAll(object);
}

QList<QObject *> &PluginManager::getObjects()
{
    return objectPool;
}

bool PluginManager::loadPlugins()
{
    QStringList pluginSpecNameFilters;
    pluginSpecNameFilters.append("*.xml");
    QString filename;
    PluginSpec *pluginSpec;
    QList<PluginSpec*> pluginsToLoad;
    bool disablePluginViewer = false;

    // Load plugin specs
    for (int i = 0; i < pluginPaths.size(); i++)
    {
        QDir dir(pluginPaths.at(i));
        dir.setNameFilters(pluginSpecNameFilters);
        QDirIterator dirIterator(dir, QDirIterator::Subdirectories);

        while (dirIterator.hasNext())
        {
            dirIterator.next();
            filename = dirIterator.fileInfo().absoluteFilePath();

            pluginSpec = new PluginSpec(filename);

            pluginMap.insert(pluginSpec->getVendor() + "." + pluginSpec->getName(), pluginSpec);
        }
    }

    // First load the core plugin
    pluginSpec = pluginMap.value(corePluginName);

    if ( !(pluginSpec && loadPlugin(pluginSpec) ) )
    {
        qDebug() << "could not load core plugin";
        return false;
    }

    qDebug() << "read selected Plugins file: " << selectedPluginsFile;
    QFile selectedPlugins(selectedPluginsFile);
    if (!selectedPlugins.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "could not open file";
        return false;
    }

    QTextStream in(&selectedPlugins);
    QString pluginToLoad = in.readLine();
    while (!pluginToLoad.isNull())
    {
        if (!pluginToLoad.startsWith('#'))
        {
            pluginSpec = pluginMap.value(pluginToLoad);
            if ( !(pluginSpec && loadPlugin(pluginSpec) ) )
            {
                qDebug() << "could not load plugin: " << pluginToLoad;
                return false;
            }

            qDebug() << pluginSpec->getCategory();
            if (pluginSpec->getCategory() == "GUI")
            {
                disablePluginViewer = true;
            }
        }

        pluginToLoad = in.readLine();
    }

    if (!disablePluginViewer)
        showPluginViewer();

    return true;
}

void PluginManager::showPluginViewer()
{
    PluginViewer* viewer = new PluginViewer(this->pluginMap.values());
    //viewer->setVisible(true);
    viewer->show();
}

bool PluginManager::loadPlugin(PluginSpec *pluginSpec)
{
    QStringList foo;
    qDebug() << "\n" << pluginSpec->getName();

    pluginSpec->loadLibrary();

    IPlugin *plugin = pluginSpec->getPlugin();

    if (plugin)
    {
        return plugin->initialize(foo);
    }

    return false;
}


