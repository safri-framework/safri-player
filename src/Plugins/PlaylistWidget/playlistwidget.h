#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include "Interfaces/iplaylistwidget.h"

namespace Ui { class PlaylistWidget; }

class PlaylistWidget : public Core::IPlaylistWidget
{
    Q_OBJECT
    
    public:

        explicit PlaylistWidget(QWidget *parent = 0);
        ~PlaylistWidget();

        virtual void showPlaylist(Core::IPlaylist *playlist) ;
        virtual void showCurrentPlaylist();
        virtual Core::IPlaylist* newPlaylist();

    public slots:

        virtual void itemsSelected(QList<Core::Item*> selection);

    private:
        Ui::PlaylistWidget *ui;
};

#endif // PLAYLISTWIDGET_H
