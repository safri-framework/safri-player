#include "playerwidgetII_plugin.h"
#include "plwidgetfactory.h"

using namespace Plugins;

bool PlayerWidgetII_Plugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    addObject(new PLWidgetFactory());
    return true;

}

PlayerWidgetII_Plugin::PlayerWidgetII_Plugin()
{
}

