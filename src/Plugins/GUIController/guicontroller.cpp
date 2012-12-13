#include "guicontroller.h"
#include <pluginmanager.h>
#include "Interfaces/iplayerwidgetfactory.h"
#include <QDebug>

GUIController::GUIController(QObject *parent) :
    currentPlayerWidget(0), currentPlayerWidgetFactory(0), currentPlaylistWidget(0)
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

QWidget *GUIController::getPlayerWidget()
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

QWidget *GUIController::getPlaylistWidget()
{
    // TODO
    return 0;
}

QList<Core::ISideBarPlugin*> GUIController::getSideBarPlugins()
{
    return QList<Core::ISideBarPlugin*>();
}

void GUIController::objectAddedToObjectPool(QObject *object)
{
    Core::IPlayerWidgetFactory *playerWidgetFactory = qobject_cast<Core::IPlayerWidgetFactory*>(object);
    if (playerWidgetFactory != 0)
    {
        qDebug() << "GUIController::IPlayerWidgetFactory class added";
        switchPlayerWidgetFactory(playerWidgetFactory);
    }
}

void GUIController::switchPlayerWidgetFactory(Core::IPlayerWidgetFactory *factory)
{
    currentPlayerWidgetFactory = factory;
    delete currentPlayerWidget;
    currentPlayerWidget = 0;
    Q_EMIT playerWidgetChanged();
}
