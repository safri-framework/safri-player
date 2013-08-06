#include "TabbedPLWidgetFactory.h"
#include "TabbedPlaylistWidget.h"

TabbedPLWidgetFactory::TabbedPLWidgetFactory(QObject *parent) :
    IPlaylistWidgetFactory(parent)
{
}

Core::IPlaylistWidget *TabbedPLWidgetFactory::createWidget()
{
    return new TabbedPlaylistWidget();
}

QString TabbedPLWidgetFactory::getName()
{
    return "Safri Tabbed Playlistwidget";
}
