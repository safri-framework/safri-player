#ifndef PLAYERWIDGETFACTORY_H
#define PLAYERWIDGETFACTORY_H

#include "Interfaces/IPlayerWidgetFactory.h"
#include "Interfaces/IPlayerWidget.h"


class PlayerWidgetFactory : public Core::IPlayerWidgetFactory
{
    public:

        explicit PlayerWidgetFactory();


        virtual IPlayerWidget* createWidget();
        virtual QString getName();

};

#endif // PLAYERWIDGETFACTORY_H
