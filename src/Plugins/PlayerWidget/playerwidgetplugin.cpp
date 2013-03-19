#include "playerwidgetplugin.h"
#include "playerwidgetfactory.h"

using namespace Plugins;

PlayerWidgetPlugin::PlayerWidgetPlugin()
{
}

bool PlayerWidgetPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
   addObject(new PlayerWidgetFactory());
    return true;
}

