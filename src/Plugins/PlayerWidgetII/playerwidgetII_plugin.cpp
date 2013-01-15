#include "playerwidgetII_plugin.h"
#include "plwidgetfactory.h"

using namespace Plugins;

bool PlayerWidgetII_Plugin::initialize(QStringList &arguments)
{
    addObject(new PLWidgetFactory());
    return true;

}

PlayerWidgetII_Plugin::PlayerWidgetII_Plugin()
{
}

Q_EXPORT_PLUGIN2(PlayerWidgetII_Plugin, PlayerWidgetII_Plugin)
