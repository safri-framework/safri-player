#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include "GUIController_global.h"
#include "Interfaces/iguicontroller.h"

class GUICONTROLLERSHARED_EXPORT GUIController : public Core::IGUIController
{
    Q_OBJECT
    public:

        explicit GUIController(QObject *parent = 0);

        virtual QWidget* getPlayerWidget();
        virtual QWidget* getPlaylistWidget();
        virtual QList<Core::ISideBarPlugin*> getSideBarPlugins();
};

#endif // GUICONTROLLER_H
