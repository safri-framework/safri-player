#include "guicontrollerplugin.h"
#include "guicontroller.h"

using namespace Plugins;

GUIControllerPlugin::GUIControllerPlugin()
{
}

bool GUIControllerPlugin::initialize(QStringList &arguments)
{
    addObject( new GUIController() );
}

Q_EXPORT_PLUGIN2(GUIControllerPlugin, GUIControllerPlugin)
