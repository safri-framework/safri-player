#include "playerwidgetfactory.h"
#include "playerwidget.h"

PlayerWidgetFactory::PlayerWidgetFactory()
{
}

QWidget *PlayerWidgetFactory::createWidget()
{
    return new PlayerWidget;
}

QString PlayerWidgetFactory::getName()
{
    return "Safri Default Player";
}
