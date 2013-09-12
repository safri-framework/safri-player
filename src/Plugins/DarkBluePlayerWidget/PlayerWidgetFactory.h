#ifndef PLAYERWIDGETFACTORY_H
#define PLAYERWIDGETFACTORY_H

#include "Interfaces/IPlayerWidgetFactory.h"

class PlayerWidgetFactory : public Core::IPlayerWidgetFactory
{
    Q_OBJECT
    public:

        explicit PlayerWidgetFactory(QObject *parent = 0);

        virtual IPlayerWidget*  createWidget();
        virtual QString         getName();
};

#endif // PLAYERWIDGETFACTORY_H
