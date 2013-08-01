#include "PlayerWidgetFactory.h"
#include "DarkBluePlayerWidget.h"

PlayerWidgetFactory::PlayerWidgetFactory(QObject *parent) :
    IPlayerWidgetFactory(parent)
{
}

IPlayerWidget *PlayerWidgetFactory::createWidget()
{
    return new DarkBluePlayerWidget();
}

QString PlayerWidgetFactory::getName()
{
    return "DarkBlue PlayerWidget";
}
