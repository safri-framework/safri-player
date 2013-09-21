#include "CorePlugin.h"

#include "Interfaces/ICore.h"
#include "../PluginSystem/pluginmanager.h"

#include <QDebug>

using namespace Plugins;

CorePlugin::CorePlugin()
{
    qDebug() << "CorePlugin";
}

CorePlugin::~CorePlugin()
{
    qDebug() << "~CorePlugin";
    delete Core::ICore::m_instance;
}

bool CorePlugin::initialize(QStringList  &arguments)
{
    Q_UNUSED(arguments)
    qDebug() << "CorePlugin::initialize(...)";

    // create and store instance to ICore object
    Core::ICore::m_instance = new Core::ICore();

    return true;
}


