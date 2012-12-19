#ifndef PLAYLISTWIDGETFACTORY_H
#define PLAYLISTWIDGETFACTORY_H

#include "PlaylistWidget_global.h"
#include "Interfaces/iplaylistwidgetfactory.h"

class PLAYLISTWIDGETSHARED_EXPORT PlaylistWidgetFactory : public Core::IPlaylistWidgetFactory
{
    Q_OBJECT
    public:

        explicit PlaylistWidgetFactory(QObject *parent = 0);

        virtual Core::IPlaylistWidget* createWidget();
        virtual QString getName();
};

#endif // PLAYLISTWIDGETFACTORY_H
