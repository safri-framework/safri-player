#ifndef IGUICONTROLLER_H
#define IGUICONTROLLER_H

#include "..\CorePlugin_global.h"
#include <QObject>
#include <QList>

class QWidget;

namespace Core
{
    class ISideBarPlugin;

    class COREPLUGINSHARED_EXPORT IGUIController : public QObject
    {
        Q_OBJECT
        public:

            virtual ~IGUIController();

            virtual QWidget* getPlayerWidget() = 0;
            virtual QWidget* getPlaylistWidget() = 0;
            virtual QList<ISideBarPlugin*> getSideBarPlugins() = 0;
    };
}

#endif // IGUICONTROLLER_H
