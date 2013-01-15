#include "playerwidgetplugin.h"
#include "playerwidgetfactory.h"

using namespace Plugins;

PlayerWidgetPlugin::PlayerWidgetPlugin()
{
}

bool PlayerWidgetPlugin::initialize(QStringList &arguments)
{
   addObject(new PlayerWidgetFactory());
    return true;
}

Q_EXPORT_PLUGIN2(PlayerWidgetPlugin, PlayerWidgetPlugin)
