#ifndef PLAYLISTTABWIDGET_H
#define PLAYLISTTABWIDGET_H

#include <QTabWidget>

class PlaylistTabWidget : public QTabWidget
{
    Q_OBJECT
    public:
        explicit PlaylistTabWidget(QWidget *parent = 0);

    signals:

        void lastTabRemoved(PlaylistTabWidget *tabWidget);

    private slots:

        void onTabCloseRequested(int index);

    public slots:
};

#endif // PLAYLISTTABWIDGET_H
