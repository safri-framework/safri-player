#include "TabbedPlaylistWidgetPlugin.h"
#include "TabbedPLWidgetFactory.h"
#include "TabbedPlaylistSettingsWidget.h"
#include "Settings/SettingsManager.h"
#include "Interfaces/ICore.h"
#include <QDebug>

TabbedPlaylistWidgetPlugin::TabbedPlaylistWidgetPlugin()
{
}

bool TabbedPlaylistWidgetPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    addObject(new TabbedPLWidgetFactory(this) );
    addObject( new TabbedPlaylistSettingsWidget( Core::ICore::settingsManager()->getModule("org.safri.tabbedplaylist") ) );
    return true;
}
