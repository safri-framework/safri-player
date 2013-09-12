#include "PlaylistView.h"
//#include "Songtree/SongTreeProxyModel.h"
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

    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(QApplication::instance(), SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(focusChanged(QWidget*,QWidget*)));
}


void PlaylistView::mousePressEvent (QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);
    startDragPosition = event->pos();
}


void PlaylistView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->pos() - startDragPosition).manhattanLength() < QApplication::startDragDistance())
    {
        qDebug()<<"blah";
        return;
    }

    QModelIndexList modelIndexList = selectionModel()->selectedRows(0);


    QMimeData *mimeData = 0;

    mimeData = this->model()->mimeData(modelIndexList);

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
    QTreeView::dragEnterEvent(event);
    event->accept();
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
    return selectionModel()->selectedRows(0);
}

void PlaylistView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);

    connect (model, SIGNAL(selectedIndexesMoved(QItemSelection&) ), this, SLOT(selectIndexes(QItemSelection&)));

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

void PlaylistView::setName(QString name)
{
    this->name = name;
}

void PlaylistView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        QModelIndexList indexes = selectionModel()->selectedRows(0);

        QList<int> intList;
        for (int i = 0; i < indexes.size(); i++)
        {
            intList.append(indexes.at(i).row());
        }

        qSort(intList.begin(), intList.end());

        PlaylistModel* playlistModel = qobject_cast<PlaylistModel*>( this->model() );

        QSharedPointer<Core::IPlaylist> playlist = playlistModel->getPlaylist();

        for(int i = intList.size()-1;  i >= 0 ; i--)
        {
            playlist->deleteMedia(intList.at(i));
        }

    }
}

void PlaylistView::dragMoveEvent(QDragMoveEvent *event)
{
    QTreeView::dragMoveEvent(event);
}

void PlaylistView::focusChanged(QWidget *oldFocus, QWidget *newFocus)
{
    QPushButton* btn = qobject_cast<QPushButton*>(newFocus);
    if(oldFocus == this && !btn)
    {
        //this->selectionModel()->clear();
    }
}

void PlaylistView::selectIndexes(QItemSelection &newSelection)
{
    selectionModel()->clear();
    selectionModel()->select(newSelection, QItemSelectionModel::Rows | QItemSelectionModel::Current | QItemSelectionModel::Select);
}
