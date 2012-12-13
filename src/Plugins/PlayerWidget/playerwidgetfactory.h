#ifndef PLAYERWIDGETFACTORY_H
#define PLAYERWIDGETFACTORY_H

#include "Interfaces/iplayerwidgetfactory.h"

class PlayerWidgetFactory : public Core::IPlayerWidgetFactory
{
    public:

        explicit PlayerWidgetFactory();

        virtual QWidget* createWidget();
        virtual QString getName();
};

#endif // PLAYERWIDGETFACTORY_H
