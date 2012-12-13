#include "guicontrollerplugin.h"
#include "guicontroller.h"


GUIControllerPlugin::GUIControllerPlugin()
{
}

bool GUIControllerPlugin::initialize(QStringList &arguments)
{
    addObject( new GUIController() );
}

Q_EXPORT_PLUGIN2(GUIControllerPlugin, GUIControllerPlugin)
