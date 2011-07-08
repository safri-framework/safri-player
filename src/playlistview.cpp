#include "playlistview.h"

PlaylistView::PlaylistView(QWidget *parent) :
    QTreeView(parent)
{
    this->setHeaderHidden(false);

    this->setAcceptDrops(true);
    //this->setDragDropMode(QAbstractItemView::dragDropMode());

}


void PlaylistView::mousePressEvent (QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);


    startDragPosition = event->pos();

}


void PlaylistView::mouseMoveEvent(QMouseEvent *event)
{
    QModelIndex index = this->indexAt(startDragPosition);

    if ((event->pos() - startDragPosition).manhattanLength()
         < QApplication::startDragDistance())
        return;
    if (!(index.isValid()))
        return;

    QModelIndexList modelIndexList;
    modelIndexList.append(index);
    QDrag *drag = new QDrag(this);


    QMimeData *mimeData = this->model()->mimeData(modelIndexList);

    if (!(event->buttons() & Qt::RightButton))
    {
        mimeData->setUrls(QList<QUrl>());
        drag->setMimeData(mimeData);
        drag->exec(Qt::MoveAction);
    }

    if (!(event->buttons() & Qt::LeftButton))
    {
        drag->setMimeData(mimeData);
        drag->exec(Qt::CopyAction);
    }

}

void PlaylistView::dragEnterEvent(QDragEnterEvent *event)
{
    QTreeView::dragEnterEvent(event);

}

/*
QPixmap QAbstractItemViewPrivate::renderToPixmap(const QModelIndexList &indexes, QRect *r) const
{
    Q_ASSERT(r);
    QItemViewPaintPairs paintPairs = draggablePaintPairs(indexes, r);
    if (paintPairs.isEmpty())
        return QPixmap();
    QPixmap pixmap(r->size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QStyleOptionViewItemV4 option = viewOptionsV4();
    option.state |= QStyle::State_Selected;
    for (int j = 0; j < paintPairs.count(); ++j) {
        option.rect = paintPairs.at(j).first.translated(-r->topLeft());
        const QModelIndex &current = paintPairs.at(j).second;
        delegateForIndex(current)->paint(&painter, option, current);
    }
    return pixmap;
}
*/

QModelIndexList PlaylistView::selectedIndexes() const
{
    return QTreeView::selectedIndexes();
}
