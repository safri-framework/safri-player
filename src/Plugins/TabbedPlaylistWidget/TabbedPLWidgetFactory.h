#ifndef TABBEDPLWIDGETFACTORY_H
#define TABBEDPLWIDGETFACTORY_H

#include "tabbedplaylistwidget_global.h"
#include "Interfaces/IPlaylistWidgetFactory.h"

namespace Core {
    class IPlaylistWidget;
}

class TABBEDPLAYLISTWIDGETSHARED_EXPORT TabbedPLWidgetFactory : public Core::IPlaylistWidgetFactory
{
    Q_OBJECT
    public:

        TabbedPLWidgetFactory(QObject* parent = 0);

        virtual Core::IPlaylistWidget* createWidget();
        virtual QString getName();
};

#endif // TABBEDPLWIDGETFACTORY_H
