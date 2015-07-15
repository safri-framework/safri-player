#include "SpotifyLookupSidebarWidget.h"
#include <QVariant>
#include <QtWidgets/QPushButton>


SpotifyLookupSidebarWidget::SpotifyLookupSidebarWidget()

{
    _button = new QPushButton();
    _button->setText("Spotify");
    _button->setProperty("style", QVariant("tabStyle"));
    _button->setCheckable(true);
    _search = new SpotifySearch();

    connect(_button, SIGNAL(clicked(bool)), this, SIGNAL(show(bool)));
}

QWidget *SpotifyLookupSidebarWidget::getSideBarWidget()
{
    return _search;
}

QString SpotifyLookupSidebarWidget::getName()
{
     return "Spotify";
}

QWidget *SpotifyLookupSidebarWidget::getMenuBarWidget()
{
    return _button;
}

bool SpotifyLookupSidebarWidget::isVisible()
{
    return false;
}
