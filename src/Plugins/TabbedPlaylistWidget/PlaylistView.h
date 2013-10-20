#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QTreeView>
#include <QDebug>

#include "PlaylistModel.h"
#include <QUrl>
#include <QList>
#include <QMouseEvent>
#include <QApplication>
#include <QModelIndexList>

class PlaylistHeaderView;

class PlaylistView : public QTreeView
{
    Q_OBJECT
    public:
        explicit PlaylistView(QString name, QWidget *parent = 0);

        QModelIndexList selectedIndexes() const;

        void setModel(QAbstractItemModel *model);

        QString     getName();
        void        setName(QString name);

    private:

        void setSectionVisibilityFromSettings(QString selectedHeaders);
        void saveSectionVisibilitySettings();

        QPoint startDragPosition;
        bool dragStarted;
        QString name;
        PlaylistHeaderView* headerView;


    signals:

        void deleteSongs(QList<int> list);

    public slots:

        void mousePressEvent (QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void dragEnterEvent(QDragEnterEvent *event);
        void keyPressEvent(QKeyEvent *event);
        void dragMoveEvent(QDragMoveEvent *event);
        void focusChanged(QWidget* oldFocus, QWidget* newFocus);
        void selectIndexes(QItemSelection &newSelection);

    private slots:

        void onCustomContextMenuRequested(const QPoint &pos);
        void onSectionVisibilityChanged(int logicalIndex);
        void onSettingsChanged(QString setting);

};

#endif // PLAYLISTVIEW_H
