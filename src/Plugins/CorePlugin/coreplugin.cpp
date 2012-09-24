#include "coreplugin.h"

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
    return true;
}

Q_EXPORT_PLUGIN2(CorePlugin, CorePlugin)
