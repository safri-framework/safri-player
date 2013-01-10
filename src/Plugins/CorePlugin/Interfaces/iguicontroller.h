#ifndef IGUICONTROLLER_H
#define IGUICONTROLLER_H

#include "../CorePlugin_global.h"
#include <QObject>
#include <QList>

class QWidget;

namespace Core
{
    class ISideBarPlugin;
    class IPlaylistWidget;

    class COREPLUGINSHARED_EXPORT IGUIController : public QObject
    {
        Q_OBJECT
        public:

            virtual ~IGUIController();

            virtual QWidget* getPlayerWidget() = 0;
            virtual IPlaylistWidget* getPlaylistWidget() = 0;
            virtual QList<ISideBarPlugin*> getSideBarPlugins() = 0;

        signals:

            void playerWidgetChanged();
            void playlistWidgetChanged();
    };
}

#endif // IGUICONTROLLER_H
