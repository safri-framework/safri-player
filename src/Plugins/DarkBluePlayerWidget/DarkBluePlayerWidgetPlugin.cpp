#include "DarkBluePlayerWidgetPlugin.h"
#include "PlayerWidgetFactory.h"
#include <QDebug>

using namespace Plugins;

DarkBluePlayerWidgetPlugin::DarkBluePlayerWidgetPlugin()
{
}

bool DarkBluePlayerWidgetPlugin::initialize(QStringList &arguments)
{
    qDebug() << "DarkBluePlayerWidgetPlugin";
    addObject( new PlayerWidgetFactory(this) );

    return true;
}
