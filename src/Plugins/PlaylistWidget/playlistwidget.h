#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QModelIndex>

#include "Interfaces/iplaylistwidget.h"
#include <QPixmap>
#include <QtWidgets/QLabel>
#include <QModelIndex>

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
        bool isCurrentPlayingPlaylist();

    public slots:
        virtual void itemsSelected(QList<Core::Item*> selection);
        void isAnimated(bool animated);

    private slots:
        void on_playlistView_doubleClicked(const QModelIndex &index);
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void newPlaylist(QSharedPointer<Core::IPlaylist> pl);
        void deleteSlot();

    private:
        void setPlaylist(QSharedPointer<Core::IPlaylist> pl);
        QPixmap screenshot;
        QLabel screenshotLabel;
        PlaylistModel* playlistModel;
        Ui::PlaylistWidget *ui;
        QSharedPointer<Core::IPlaylist> currentPL;
        bool isCurrentPl;
        QAction* deleteAction;
        QAction* deselectAction;
        static bool indexLessThan(QModelIndex a, QModelIndex b);

};

#endif // PLAYLISTWIDGET_H
