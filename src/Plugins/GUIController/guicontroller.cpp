#include "guicontroller.h"
#include <pluginmanager.h>
#include "Interfaces/IPlayerWidgetFactory.h"
#include "Interfaces/IPlaylistWidgetFactory.h"
#include "Interfaces/IPlaylistWidget.h"
#include <QDebug>
#include <QApplication>

GUIController::GUIController(QObject *parent) :
    IGUIController(parent), currentPlayerWidget(0), currentPlayerWidgetFactory(0), currentPlaylistWidget(0)
{
    QList<Core::IPlayerWidgetFactory*> playerFactories = PluginSystem::PluginManager::instance()->getObjects<Core::IPlayerWidgetFactory>();
    if (playerFactories.size() > 0)
    {
        Core::IPlayerWidgetFactory *playerWidgetFactory =  playerFactories.at(0);
        qDebug() << playerWidgetFactory->getName();
        switchPlayerWidgetFactory(playerWidgetFactory);
    }

    connect(PluginSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)), this, SLOT(objectAddedToObjectPool(QObject*)));
}

IPlayerWidget* GUIController::getPlayerWidget()
{
    if (currentPlayerWidget == 0)
    {
        if (currentPlayerWidgetFactory != 0)
        {
            currentPlayerWidget = currentPlayerWidgetFactory->createWidget();
        }
    }
    return currentPlayerWidget;
}

Core::IPlaylistWidget *GUIController::getPlaylistWidget()
{
    if (currentPlaylistWidget == 0)
    {
        if (currentPlaylistWidgetFactory != 0)
        {
            currentPlaylistWidget = currentPlaylistWidgetFactory->createWidget();
        }
    }
    return currentPlaylistWidget;
}

QList<Core::ISideBarPlugin*> GUIController::getSideBarPlugins()
{
    //fettes TODO! Hier muss noch eine lokale Liste der SideBar Plugins angelegt werden.
    return QList<Core::ISideBarPlugin*>();
}

bool GUIController::hasFocus()
{
    if ( QApplication::focusWidget() == 0 )
    {
        return false;
    }

    return true;
}

void GUIController::objectAddedToObjectPool(QObject *object)
{
    Core::IPlayerWidgetFactory *playerWidgetFactory = qobject_cast<Core::IPlayerWidgetFactory*>(object);
    if (playerWidgetFactory != 0)
    {
        qDebug() << "GUIController::IPlayerWidgetFactory class added";
        switchPlayerWidgetFactory(playerWidgetFactory);
        return;
    }

    Core::IPlaylistWidgetFactory *playlistWidgetFactory = qobject_cast<Core::IPlaylistWidgetFactory*>(object);
    if (playlistWidgetFactory != 0)
    {
        qDebug() << "GUIController::IPlaylistWidgetFactory class added";
        switchPlaylistWidgetFactory(playlistWidgetFactory);
        return;
    }
}

void GUIController::switchPlayerWidgetFactory(Core::IPlayerWidgetFactory *factory)
{
    currentPlayerWidgetFactory = factory;
    delete currentPlayerWidget;
    currentPlayerWidget = 0;
    Q_EMIT playerWidgetChanged();
}

void GUIController::switchPlaylistWidgetFactory(Core::IPlaylistWidgetFactory *factory)
{
    currentPlaylistWidgetFactory = factory;
    delete currentPlaylistWidget;
    currentPlaylistWidget = 0;
    Q_EMIT playlistWidgetChanged();
}
