#include "playerwidgetfactory.h"
#include "playerwidget.h"

PlayerWidgetFactory::PlayerWidgetFactory()
{
}

IPlayerWidget *PlayerWidgetFactory::createWidget()
{
    return new PlayerWidget;
}

QString PlayerWidgetFactory::getName()
{
    return "Safri Default Player";
}
