#ifndef PLWIDGETFACTORY_H
#define PLWIDGETFACTORY_H


#include "PlayerWidgetII_global.h"
#include "Interfaces/IPlayerWidgetFactory.h"


class PLAYERWIDGETIISHARED_EXPORT PLWidgetFactory : public Core::IPlayerWidgetFactory
{
public:
    PLWidgetFactory();
    virtual IPlayerWidget* createWidget();
    virtual QString getName();
};

#endif // PLWIDGETFACTORY_H
