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
class PlaylistView;

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

        bool isCurrentPlayingView(QObject* listView);

    private slots:

        void playlistViewDoubleClicked(const QModelIndex &index);
        void lastTabRemoved(PlaylistTabWidget* tabWidget);
        void addNewTab(PlaylistTabWidget* tabWidget);
        void playbackControllerStateChanged(Core::playState state);
        void onTabWidgetCostumContextMenuRequested(const QPoint &pos);
        void splitTabWidgetView(PlaylistTabWidget* tabWidget, int index);


    private:

        PlaylistTabWidget*  addNewTabWidget();
        void                removeCurrentTabIcon();
        void                setCurrentTabIcon();

        Ui::TabbedPlaylistWidget *ui;
        PlaylistTabWidget* currentPlaylistTabWidget;
        PlaylistView* currentPlayingListView;
        int currentPlaylistIndex;
        int newTabCount;
        Core::playState currentState;
};

#endif // TABBEDPLAYLISTWIDGET_H
