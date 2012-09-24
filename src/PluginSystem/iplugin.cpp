#include "iplugin.h"
#include "pluginmanager.h"

using namespace PluginSystem;

QString IPlugin::errorString()
{
    return errorStr;
}

void IPlugin::addObject(QObject *object)
{
    PluginManager::instance()->addObject(object);
}

void IPlugin::removeObject(QObject *object)
{
    PluginManager::instance()->removeObject(object);
}

bool IPlugin::shutdown()
{
    return true;
}
