#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QModelIndex>

#include "Interfaces/iplaylistwidget.h"
#include <QPixmap>
#include <QLabel>

namespace Ui { class PlaylistWidget; }

class PlaylistModel;

class PlaylistWidget : public Core::IPlaylistWidget
{
    Q_OBJECT
    
    public:

        explicit PlaylistWidget(QWidget *parent = 0);
        ~PlaylistWidget();

        virtual void showPlaylist(QSharedPointer<Core::IPlaylist> playlist) ;
        virtual void showCurrentPlaylist();
        virtual QSharedPointer<Core::IPlaylist> newPlaylist();

    public slots:

        virtual void itemsSelected(QList<Core::Item*> selection);
        void isAnimated(bool animated);

    private slots:

        void on_playlistView_doubleClicked(const QModelIndex &index);

        void on_pushButton_clicked();

private:

        QPixmap screenshot;
        QLabel screenshotLabel;
            PlaylistModel* playlistModel;
            Ui::PlaylistWidget *ui;
};

#endif // PLAYLISTWIDGET_H
