#ifndef IPLAYERWIDGETFACTORY_H
#define IPLAYERWIDGETFACTORY_H

#include <QWidget>

#include "../CorePlugin_global.h"
#include "IPlayerWidget.h"



namespace Core
{
    class COREPLUGINSHARED_EXPORT IPlayerWidgetFactory : public QObject
    {
        Q_OBJECT
        public:

            virtual ~IPlayerWidgetFactory();

            virtual IPlayerWidget* createWidget() = 0;
            virtual QString getName() = 0;

    };
}

#endif // IPLAYERWIDGETFACTORY_H
