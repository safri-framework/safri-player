#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include "GUIController_global.h"
#include "Interfaces/iguicontroller.h"
#include "Interfaces/IPlayerWidget.h"

namespace Core
{
    class IPlayerWidgetFactory;
    class IPlaylistWidgetFactory;
    class IPlaylistWidget;
}

class GUICONTROLLERSHARED_EXPORT GUIController : public Core::IGUIController
{
    Q_OBJECT
    public:

        explicit GUIController(QObject *parent = 0);

        virtual IPlayerWidget* getPlayerWidget();
        virtual Core::IPlaylistWidget* getPlaylistWidget();
        virtual QList<Core::ISideBarPlugin*> getSideBarPlugins();

    private slots:

        void objectAddedToObjectPool(QObject *object);

    private:

        void switchPlayerWidgetFactory(Core::IPlayerWidgetFactory* factory);
        void switchPlaylistWidgetFactory(Core::IPlaylistWidgetFactory* factory);

        IPlayerWidget* currentPlayerWidget;
        Core::IPlayerWidgetFactory *currentPlayerWidgetFactory;

        Core::IPlaylistWidget* currentPlaylistWidget;
        Core::IPlaylistWidgetFactory* currentPlaylistWidgetFactory;

};

#endif // GUICONTROLLER_H
