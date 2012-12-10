#include "pluginmanager.h"
#include "pluginspec.h"
#include "pluginviewer.h"

#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QPluginLoader>

using namespace PluginSystem;

PluginManager *PluginManager::m_instance = 0;

PluginManager::PluginManager(QString corePluginName, QStringList pluginPaths)
    : QObject(0), pluginPaths(pluginPaths), corePluginName(corePluginName)
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
    PluginSpec *pluginSpec, *corePluginSpec;
    QList<PluginSpec*> pluginsToLoad;

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

            if (pluginSpec->getName() == corePluginName)
            {
                corePluginSpec = pluginSpec;
            }
            else
            {
                pluginsToLoad.append(pluginSpec);
            }
        }
    }

    // Load plugins
    if (!loadPlugin(corePluginSpec))
        return false;

    plugins.append(corePluginSpec);

    for (int i = 0; i < pluginsToLoad.size(); i++)
    {
        pluginSpec = pluginsToLoad.at(i);
        loadPlugin(pluginSpec);
        plugins.append(pluginSpec);
    }

    return true;
}

void PluginManager::showPluginViewer()
{
    PluginViewer* viewer = new PluginViewer(this->plugins);
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


