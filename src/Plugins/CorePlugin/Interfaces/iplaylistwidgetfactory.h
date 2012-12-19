#ifndef IPLAYLISTWIDGETFACTORY_H
#define IPLAYLISTWIDGETFACTORY_H

#include "../CorePlugin_global.h"
#include <QObject>

namespace Core
{
    class IPlaylistWidget;

    class COREPLUGINSHARED_EXPORT IPlaylistWidgetFactory : public QObject
    {
        Q_OBJECT
        public:

            explicit IPlaylistWidgetFactory(QObject *parent = 0);

            virtual IPlaylistWidget* createWidget() = 0;
            virtual QString getName() = 0;
    };

}

#endif // IPLAYLISTWIDGETFACTORY_H
