#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QTreeView>
#include <QDebug>
#include "audiofile.h"
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


signals:

public slots:

    void mousePressEvent (QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);



};

#endif // PLAYLISTVIEW_H
