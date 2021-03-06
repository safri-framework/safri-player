#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QTreeView>
#include <QDebug>

#include "playlistmodel.h"
#include <QUrl>
#include <QList>
#include <QMouseEvent>
#include <QApplication>
#include <QModelIndexList>


class PlaylistView : public QTreeView
{
    Q_OBJECT
public:
    explicit PlaylistView(QWidget *parent = 0);

    QModelIndexList selectedIndexes() const;

private:
    QPoint startDragPosition;
    bool dragStarted;

signals:

    void deleteSongs(QList<int> list);

public slots:
    void mousePressEvent (QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void focusChanged(QWidget* oldFocus, QWidget* newFocus);

};

#endif // PLAYLISTVIEW_H
