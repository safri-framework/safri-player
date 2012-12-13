#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include "GUIController_global.h"
#include "Interfaces/iguicontroller.h"

namespace Core
{
    class IPlayerWidgetFactory;
}

class GUICONTROLLERSHARED_EXPORT GUIController : public Core::IGUIController
{
    Q_OBJECT
    public:

        explicit GUIController(QObject *parent = 0);

        virtual QWidget* getPlayerWidget();
        virtual QWidget* getPlaylistWidget();
        virtual QList<Core::ISideBarPlugin*> getSideBarPlugins();

    public slots:

        void objectAddedToObjectPool(QObject *object);

    private:

        void switchPlayerWidgetFactory(Core::IPlayerWidgetFactory* factory);

        QWidget* currentPlayerWidget;
        Core::IPlayerWidgetFactory *currentPlayerWidgetFactory;

        QWidget* currentPlaylistWidget;
};

#endif // GUICONTROLLER_H
