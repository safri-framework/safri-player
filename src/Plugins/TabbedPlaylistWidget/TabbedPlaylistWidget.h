#ifndef TABBEDPLAYLISTWIDGET_H
#define TABBEDPLAYLISTWIDGET_H

#include "Interfaces/iplaylistwidget.h"
#include "iplaybackcontroller.h"
#include <QSharedPointer>
#include <QModelIndex>

namespace Ui {
class TabbedPlaylistWidget;
}

namespace Core {
    class IPlaylist;
}

class QTabWidget;
class PlaylistTabWidget;

class TabbedPlaylistWidget : public Core::IPlaylistWidget
{
    Q_OBJECT
    public:

        explicit TabbedPlaylistWidget(QWidget *parent = 0);
        ~TabbedPlaylistWidget();

   // ***** IPlaylist Interface *****
        virtual void showPlaylist(QSharedPointer<Core::IPlaylist> playlist);
        virtual void showCurrentPlaylist();
        virtual QSharedPointer<Core::IPlaylist> newPlaylist();

    public slots:

        virtual void isAnimated(bool animated);
        virtual void itemsSelected(QList<Core::Item*> selection);
    // *******************************

        PlaylistTabWidget* addNewPlaylist(QString name, PlaylistTabWidget *tabWidget = 0);
        PlaylistTabWidget* addNewPlaylist(QString name, QSharedPointer<Core::IPlaylist> playlist, PlaylistTabWidget *tabWidget = 0);

    private slots:

        void playlistViewDoubleClicked(const QModelIndex &index);
        void lastTabRemoved(PlaylistTabWidget* tabWidget);
        void playbackControllerStateChanged(Core::playState state);
        void onTabWidgetCostumContextMenuRequested(const QPoint &pos);

    private:

        Ui::TabbedPlaylistWidget *ui;
        PlaylistTabWidget* currentPlaylistTabWidget;
        int currentPlaylistIndex;
};

#endif // TABBEDPLAYLISTWIDGET_H
