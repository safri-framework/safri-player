#ifndef IPLAYLISTWIDGET_H
#define IPLAYLISTWIDGET_H

#include "../CorePlugin_global.h"
#include <QWidget>
#include <QList>

namespace Core
{    
    class IPlaylist;
    class Item;

    class COREPLUGINSHARED_EXPORT IPlaylistWidget : public QWidget
    {
        Q_OBJECT
        public:

            explicit IPlaylistWidget(QWidget *parent = 0);
            virtual ~IPlaylistWidget();

            virtual void showPlaylist(QSharedPointer<IPlaylist> playlist) = 0;
            virtual void showCurrentPlaylist() = 0;
            virtual QSharedPointer<IPlaylist> newPlaylist() = 0;

        public slots:

            virtual void isAnimated(bool animated) = 0;
            virtual void itemsSelected(QList<Item*> selection) = 0;
    };

}

#endif // IPLAYLISTWIDGET_H
