#include "coreplugin.h"

#include "icore.h"

#include <QDebug>

using namespace Core;

CorePlugin::CorePlugin()
{
    qDebug() << "CorePlugin";
}

CorePlugin::~CorePlugin()
{
    qDebug() << "~CorePlugin";
}

bool CorePlugin::initialize(QStringList __attribute__ ((unused)) &arguments)
{
    qDebug() << "CorePlugin::initialize(...)";

    // create and store instance to ICore object
    ICore::m_instance = new ICore();

    return true;
}

Q_EXPORT_PLUGIN2(CorePlugin, CorePlugin)
