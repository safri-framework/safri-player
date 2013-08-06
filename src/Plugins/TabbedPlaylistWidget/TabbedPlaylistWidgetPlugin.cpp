#include "TabbedPlaylistWidgetPlugin.h"
#include "TabbedPLWidgetFactory.h"

TabbedPlaylistWidgetPlugin::TabbedPlaylistWidgetPlugin()
{
}

bool TabbedPlaylistWidgetPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    addObject(new TabbedPLWidgetFactory(this) );
    return true;
}
