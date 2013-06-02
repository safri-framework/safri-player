#include "AlbumCoversPlugin.h"
#include "AlbumCoversAssetService.h"
#include "CoverSettingsWidget.h"

AlbumCoversPlugin::AlbumCoversPlugin()
{
}

bool AlbumCoversPlugin::initialize(QStringList &arguments)
{
    AlbumCoversAssetService* service = new AlbumCoversAssetService();
    CoverSettingsWidget* settingsWidget = new CoverSettingsWidget();
    connect(settingsWidget, SIGNAL(updateCovers()), service, SLOT(updateCovers()));
    addObject(service);
    addObject(settingsWidget);
    return true;
}
