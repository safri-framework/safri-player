#include "SpotifyPlugin.h"
#include <QDebug>
#include "SpotifyLookupSidebarWidget.h"
#include "SpotifyMediaBackend.h"


SpotifyPlugin::SpotifyPlugin()
{
}

bool SpotifyPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    SpotifyLookupSidebarWidget* widget = new SpotifyLookupSidebarWidget();

    addObject(widget);
    addObject(new SpotifyMediaBackend());
    return true;
}
