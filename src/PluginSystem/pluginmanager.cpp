#include "pluginmanager.h"
#include "pluginspec.h"
#include "pluginviewer.h"

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QPluginLoader>
#include <QTextStream>
#include <QFileInfo>
#include <iostream>

using namespace PluginSystem;

PluginManager *PluginManager::m_instance = 0;

PluginManager::PluginManager(QString corePluginName, QStringList pluginPaths, QString selectedPluginsFile)
    : QObject(0), pluginPaths(pluginPaths), corePluginName(corePluginName), selectedPluginsFile(selectedPluginsFile)
{
    qDebug() << "PluginManager(QStringList pluginPaths)";
#ifdef ANDROID
    qDebug() << "Android build...";
#else
    qDebug() << "Non-anrdoid build";
#endif
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
    return m_instance->objectPool;
}

bool PluginManager::loadPlugins()
{
    QStringList pluginSpecNameFilters;
    pluginSpecNameFilters.append("*.xml");
    QString filename;
    PluginSpec *pluginSpec;
    bool disablePluginViewer = false;
    QString currentPath = QDir::current().absolutePath();


    // Load plugin specs
    for (int i = 0; i < pluginPaths.size(); i++)
    {
        qDebug() << pluginPaths.at(i);
        QDir dir(pluginPaths.at(i));
        dir.setNameFilters(pluginSpecNameFilters);
        QDirIterator dirIterator(dir, QDirIterator::Subdirectories);

        while (dirIterator.hasNext())
        {
            dirIterator.next();
            filename = dirIterator.fileInfo().absoluteFilePath();

            pluginSpec = new PluginSpec(filename);

            qDebug() << "Loaded pluginspec: " << pluginSpec->getVendor() + "." + pluginSpec->getName();
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
    }

    QString pluginToLoad;
    QTextStream  in(&selectedPlugins);

    pluginToLoad = in.readLine();

    while (!pluginToLoad.isNull())
    {
        qDebug() << "selectedPlugin: " << pluginToLoad;
        if (!pluginToLoad.startsWith('#'))
        {
            pluginConfig.insert(pluginToLoad, true);
            pluginSpec = pluginMap.value(pluginToLoad);
            if ( !(pluginSpec && loadPlugin(pluginSpec) ) )
            {
                qDebug() << "could not load plugin: " << pluginToLoad;
                QDir::setCurrent(currentPath);
                return false;
            }

            qDebug() << pluginSpec->getCategory();
            if (pluginSpec->getCategory() == "GUI")
            {
                disablePluginViewer = true;
            }
        }
        else
            pluginConfig.insert(pluginToLoad.remove("#"), false);

        pluginToLoad = in.readLine();
    }

    if (!disablePluginViewer)
        showPluginViewer();

    // reset the current path, because plugin loaders would change
    // it during the loading process
    QDir::setCurrent(currentPath);

    return true;
}

void PluginManager::showPluginViewer()
{
    getPluginViewer()->show();
}

QWidget *PluginManager::getPluginViewer()
{
    return new PluginViewer(this->pluginMap.values(), this->pluginConfig);
}

bool PluginManager::isPluginEnabled(QString pluginID)
{
    QFile selectedPlugins(selectedPluginsFile);
    if (!selectedPlugins.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "could not open file";
        return false;
    }

    QTextStream  in(&selectedPlugins);
    QString currentLine;
    currentLine = in.readLine();
    while (!currentLine.isNull())
    {
        if(currentLine.contains(pluginID))
        {
            if(currentLine.startsWith("#"))
                return false;
            else
                return true;
        }
        currentLine = in.readLine();
    }

    return false;
}

bool PluginManager::setPluginEnabled(QString pluginID, bool enabled)
{
    QFile selectedPlugins(selectedPluginsFile);
    if (!selectedPlugins.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "could not open file";
        return false;
    }

    pluginID +='\n';
    QTextStream  in(&selectedPlugins);
    QString file;
    file = in.readAll();
    if(!file.contains(pluginID))
    {
        file.append(enabled ? pluginID : "#"+pluginID);
    }
    else
    {
        if(file.contains("#"+pluginID))
        {
            if(!enabled)
            {
                selectedPlugins.close();
                return true;
            }
            else
            {
                file.replace("#"+pluginID, pluginID);
            }
        }
        else
        {
            if(enabled)
            {
                selectedPlugins.close();
                return true;
            }
            else
            {
                file.replace(pluginID,"#"+pluginID);
            }
        }
    }

    selectedPlugins.close();
    selectedPlugins.open(QIODevice::ReadWrite | QIODevice::Text| QIODevice::Truncate);
    selectedPlugins.write(file.toUtf8());
    selectedPlugins.close();
    return true;
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


