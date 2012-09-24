#include "pluginmanager.h"
#include "pluginspec.h"

#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QPluginLoader>

using namespace PluginSystem;

PluginManager *PluginManager::m_instance = 0;

PluginManager::PluginManager(QStringList pluginPaths) : QObject(0), pluginPaths(pluginPaths)
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
            plugins.append(pluginSpec);

            qDebug() << "\n" << pluginSpec->getName();

            pluginSpec->loadLibrary();
            QStringList foo;

            IPlugin *plugin = pluginSpec->getPlugin();

            if (plugin)
            {
                plugin->initialize(foo);
            }
        }
    }

    return true;
}


