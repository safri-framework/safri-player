#include "PlaylistView.h"
//#include "Songtree/songtreeproxymodel.h"
#include "PlaylistModel.h"
#include <QDrag>
#include <QHeaderView>
#include <QPushButton>

PlaylistView::PlaylistView(QString name, QWidget *parent) :
    QTreeView(parent), name(name)
{
    this->setHeaderHidden(false);
    this->setAcceptDrops(true);
    this->setDragDropOverwriteMode(true);
    this->setDragDropMode(QAbstractItemView::dragDropMode());
    this->setDropIndicatorShown(true);
    this->setRootIsDecorated(false);
    this->setProperty("type", QVariant("treeView"));
    this->setProperty("ident", QVariant("playlist"));
    this->header()->setStretchLastSection(false);
    this->setAlternatingRowColors(true);

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

void PlaylistView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);
    this->header()->setSectionResizeMode(0, QHeaderView::Fixed);
    this->header()->setSectionResizeMode(1, QHeaderView::Fixed);
    this->header()->setSectionResizeMode(2, QHeaderView::Stretch);
    this->header()->setSectionResizeMode(3, QHeaderView::Stretch);
    this->header()->setSectionResizeMode(4, QHeaderView::Stretch);
    this->header()->resizeSection(7,50);
    this->header()->resizeSection(6,43);
    this->header()->setSectionResizeMode(7, QHeaderView::Fixed);
    this->header()->setSectionResizeMode(6, QHeaderView::Fixed);
    this->header()->resizeSection(0,25);
    this->header()->resizeSection(1,25);
}

QString PlaylistView::getName()
{
    return name;
}

void PlaylistView::keyPressEvent(QKeyEvent *event)
{
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


