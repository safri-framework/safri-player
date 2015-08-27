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
   // QQuickWindow::setDefaultAlphaBuffer(true);
    _quickview = new QQuickWidget();
    registerQmlTypes();
    _quickview->setSource(QUrl("/home/frime/SAFRI/trunk/src/Plugins/SpotifyPlugin/main.qml"));
    _quickview->setResizeMode(QQuickWidget::SizeRootObjectToView);
    connect(_button, SIGNAL(clicked(bool)), this, SIGNAL(show(bool)));
    _quickview->engine()->addImageProvider("spotify", new QSpotifyImageProvider());
    _quickview->setStyleSheet("background-color:\"transparent\";");
   // _quickview->setAttribute(Qt::WA_AlwaysStackOnTop);
    _quickview->setClearColor(Qt::transparent);
    _quickview->raise();

}

QWidget *SpotifyLookupSidebarWidget::getSideBarWidget()
{
    return _quickview;
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
