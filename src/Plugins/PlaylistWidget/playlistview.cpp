#include "playlistview.h"
#include "Songtree/SongTreeProxyModel.h"
#include "playlistmodel.h"
#include <QDrag>
#include <QHeaderView>
#include <QPushButton>

PlaylistView::PlaylistView(QWidget *parent) :
    QTreeView(parent)
{
    this->setHeaderHidden(false);
    this->setAcceptDrops(true);
    this->setDragDropOverwriteMode(true);
    this->setDragDropMode(QAbstractItemView::dragDropMode());
    this->setDropIndicatorShown(true);
    connect(QApplication::instance(), SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(focusChanged(QWidget*,QWidget*)));
}


void PlaylistView::mousePressEvent (QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);
    startDragPosition = event->pos();
}


void PlaylistView::mouseMoveEvent(QMouseEvent *event)
{

    if(event->buttons())
    {
        qDebug()<<"blub";
    }
    else
    {
        qDebug()<<"blab";
    }

    QModelIndex index = this->indexAt(startDragPosition);
    if ((event->pos() - startDragPosition).manhattanLength() < QApplication::startDragDistance())
    {
        qDebug()<<"blah";
        return;
    }
    if (!(index.isValid()))
        return;

    QModelIndexList modelIndexList;
    modelIndexList.append(index);


    QMimeData *mimeData = 0;
    mimeData = this->model()->mimeData(modelIndexList);
    if(mimeData)
        qDebug()<<"mime";

    if (!(event->buttons() & Qt::RightButton))
    {
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->exec(Qt::MoveAction);
        dragStarted = true;
    }


    if (!(event->buttons() & Qt::LeftButton))
    {
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->exec(Qt::CopyAction);
        dragStarted = true;
    }
}

/*
void PlaylistView::dragEnterEvent(QDragEnterEvent *event)
{
    QTreeView::dragEnterEvent(event);

}
*/

void PlaylistView::dragEnterEvent(QDragEnterEvent *event)
 {
    bool accepted = true;
    const QMimeData *mimeData = event->mimeData();

    Q_UNUSED(accepted)
    Q_UNUSED(mimeData)

//event->acceptProposedAction();
event->accept();
/*
if (mimeData->hasUrls())
    {

        QList<QUrl> urllist = mimeData->urls();
        foreach (QUrl i, urllist)
        {


        }

    }

*/
qDebug()<<"dragEnter";
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

void PlaylistView::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED( event )
    /*
    if (event->key() == Qt::Key_Delete)
    {
        QModelIndexList indexes = selectedIndexes();
        Pl* playlistProxy = (PlaylistProxyModel*) model();
        PlaylistModel* playlistModel = (PlaylistModel*) playlistProxy->sourceModel();
        Playlist* playlist = playlistModel->getPlaylist();
        playlist->deleteSong(playlistProxy->mapToSource(indexes.at(0)).row());
    }
    */
}

void PlaylistView::dragMoveEvent(QDragMoveEvent *event)
{
    Q_UNUSED( event )
    if(dragStarted)
    {


    }
}

void PlaylistView::focusChanged(QWidget *oldFocus, QWidget *newFocus)
{
    QPushButton* btn = qobject_cast<QPushButton*>(newFocus);
    if(oldFocus == this && !btn)
    {
        this->selectionModel()->clear();
    }
}


