#ifndef PLAYERWIDGETFACTORY_H
#define PLAYERWIDGETFACTORY_H

#include "Interfaces/iplayerwidgetfactory.h"
#include "Interfaces/IPlayerWidget.h"


class PlayerWidgetFactory : public Core::IPlayerWidgetFactory
{
    public:

        explicit PlayerWidgetFactory();


        virtual IPlayerWidget* createWidget();
        virtual QString getName();

};

#endif // PLAYERWIDGETFACTORY_H
