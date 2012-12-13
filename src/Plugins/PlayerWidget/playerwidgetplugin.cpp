#include "playerwidgetplugin.h"
#include "playerwidgetfactory.h"

PlayerWidgetPlugin::PlayerWidgetPlugin()
{
}

bool PlayerWidgetPlugin::initialize(QStringList &arguments)
{
    addObject(new PlayerWidgetFactory());
    return true;
}

Q_EXPORT_PLUGIN2(PlayerWidgetPlugin, PlayerWidgetPlugin)
