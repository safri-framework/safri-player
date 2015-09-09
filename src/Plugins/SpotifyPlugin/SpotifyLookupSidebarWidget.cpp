#include "SpotifyLookupSidebarWidget.h"
#include <QVariant>
#include <QtWidgets/QPushButton>
#include "../libQtSpotify/QtSpotify"

#include "../libQtSpotify/qspotify_qmlplugin.h"

SpotifyLookupSidebarWidget::SpotifyLookupSidebarWidget()

{
    _button = new QPushButton();
    _button->setText("Spotify");
    _button->setProperty("style", QVariant("tabStyle"));
    _button->setCheckable(true);
    _search = new SpotifySearch();
    _quickview = new QQuickView(0);
    registerQmlTypes();
    _quickview->setSource(QUrl("qrc:/main"));
    connect(_button, SIGNAL(clicked(bool)), this, SIGNAL(show(bool)));
    _quickviewWrapper = QWidget::createWindowContainer(_quickview);
    _quickview->engine()->addImageProvider("spotify", new QSpotifyImageProvider());
    _quickview->raise();
}

QWidget *SpotifyLookupSidebarWidget::getSideBarWidget()
{
 return _quickviewWrapper;
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
