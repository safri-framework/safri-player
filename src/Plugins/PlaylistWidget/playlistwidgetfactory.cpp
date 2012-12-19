#include "playlistwidgetfactory.h"
#include "playlistwidget.h"

PlaylistWidgetFactory::PlaylistWidgetFactory(QObject *parent) :
    IPlaylistWidgetFactory(parent)
{
}

Core::IPlaylistWidget *PlaylistWidgetFactory::createWidget()
{
    return new PlaylistWidget();
}

QString PlaylistWidgetFactory::getName()
{
    return "Safri Default Playlistwidget";
}
