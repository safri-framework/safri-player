#ifndef PLAYLISTTABBAR_H
#define PLAYLISTTABBAR_H

#include <QTabBar>

class PlaylistTabBar : public QTabBar
{
    Q_OBJECT
    public:

        explicit PlaylistTabBar(QWidget *parent = 0);

        bool eventFilter(QObject *object, QEvent *event);

    protected:

        void dragEnterEvent(QDragEnterEvent *event);
        void dragMoveEvent(QDragMoveEvent *event);

    signals:

        void tabDoubleClicked(int index);

    public slots:
    
};

#endif // PLAYLISTTABBAR_H
