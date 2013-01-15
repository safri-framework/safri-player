#include "plwidgetfactory.h"
#include "widget.h"


PLWidgetFactory::PLWidgetFactory()
{
}

IPlayerWidget *PLWidgetFactory::createWidget()
{
    return new Widget();
}

QString PLWidgetFactory::getName()
{
    return "Safri 3.0 PlayerWidget";
}
