#include "guicontrollerplugin.h"
#include "guicontroller.h"

using namespace Plugins;

GUIControllerPlugin::GUIControllerPlugin()
{
}

bool GUIControllerPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    addObject( new GUIController() );
    return true;
}

Q_EXPORT_PLUGIN2(GUIControllerPlugin, GUIControllerPlugin)
