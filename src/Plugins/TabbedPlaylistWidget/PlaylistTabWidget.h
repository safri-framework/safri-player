#ifndef PLAYLISTTABWIDGET_H
#define PLAYLISTTABWIDGET_H

#include <QTabWidget>
#include <QSharedPointer>

namespace Core
{
    class IPlaylist;
}

class PlaylistTabWidget : public QTabWidget
{
    Q_OBJECT
    public:
        explicit PlaylistTabWidget(QWidget *parent = 0);

        void removePlaylistTab(int index);
        void editTabName(int index);
        QSharedPointer<Core::IPlaylist> getPlaylist(int index);

    signals:

        void lastTabRemoved(PlaylistTabWidget *tabWidget);
        void addNewTab(PlaylistTabWidget* tabWidget);

    private slots:

        void onTabCloseRequested(int index);
        void onTabDoubleClicked(int index);
        void onAddTabButtonClicked();
        void tabTextEditedFinished();
        void abortTabTextEditing();

    private:

        int tabIndexEdit;
};

#endif // PLAYLISTTABWIDGET_H
