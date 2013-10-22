#include "PlaylistView.h"
//#include "Songtree/SongTreeProxyModel.h"
#include "PlaylistModel.h"
#include <QDrag>
#include <QHeaderView>
#include <QPushButton>
#include <QDebug>
#include <QMenu>

#include "Interfaces/ICore.h"
#include "Settings/SettingsManager.h"
#include "PlaylistHeaderView.h"

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

    this->setAlternatingRowColors(true);

    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(QApplication::instance(), SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(focusChanged(QWidget*,QWidget*)));

    Core::SettingsModule* settingsModule = Core::ICore::settingsManager()->getModule("org.safri.playlist");
    connect( settingsModule, SIGNAL( settingsChanged(QString) ), this, SLOT( onSettingsChanged(QString) ) );

    headerView = new PlaylistHeaderView(this);

    connect(headerView, SIGNAL( sectionVisibilityChanged(int) ), this, SLOT( onSectionVisibilityChanged(int) ) );

    setHeader( headerView );
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

    if(modelIndexList.size() == 0)
        return;

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

//#define OLD_HEADER

#ifdef OLD_HEADER

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

#else

    headerView->setSectionResizable(0, false);
    headerView->resizeSection(0,25);

    headerView->setSectionResizable(1, false);
    headerView->resizeSection(1,25);

    headerView->setSectionResizable(6, false);
    headerView->resizeSection(6,43);

    headerView->setSectionResizable(7, false);
    headerView->resizeSection(7,43);

    headerView->setSectionAutoResizeAvailableSpace();

#endif

    headerView->setSectionHideable(0, false);   // column for play icon
    headerView->setSectionHideable(2, false);   // title column

    //headerView->setCascadingSectionResizes(true);

    //this->header()->setSectionResizeMode(3, QHeaderView::Stretch);

    Core::SettingsModule* settings = Core::ICore::settingsManager()->getModule("org.safri.playlist");
    QString selectedHeaders = settings->getSetting("selectedHeaders").toString();

    setSectionVisibilityFromSettings(selectedHeaders);
}

QString PlaylistView::getName()
{
    return name;
}

void PlaylistView::setName(QString name)
{
    this->name = name;
}

void PlaylistView::setSectionVisibilityFromSettings(QString selectedHeaders)
{
    QStringList selectedHeadersList = selectedHeaders.split(";", QString::SkipEmptyParts);
    bool hide;

    if ( headerView->count() >= 0)
    {
        headerView->setSectionHidden(0, false);

        for (int i = 1; i < headerView->count(); i++)
        {
            hide = ! selectedHeadersList.contains( QString::number(i) );

            headerView->setSectionHidden(i, hide);
        }
    }
}

void PlaylistView::saveSectionVisibilitySettings()
{
    Core::SettingsModule* settings = Core::ICore::settingsManager()->getModule("org.safri.playlist");

    QString selectedHeaders = "";

    for (int i = 1; i < headerView->count(); i++)
    {
        if ( !headerView->isSectionHidden(i) )
        {
            if ( !selectedHeaders.isEmpty() )
            {
                selectedHeaders += ";";
            }

            selectedHeaders += QString::number(i);
        }
    }

    settings->setSetting("selectedHeaders", selectedHeaders);
    Core::ICore::settingsManager()->saveSettings();
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

void PlaylistView::onCustomContextMenuRequested(const QPoint &pos)
{
    qDebug() << "KONTEXT MENU";
}

void PlaylistView::onSectionVisibilityChanged(int logicalIndex)
{
    Q_UNUSED(logicalIndex)
    saveSectionVisibilitySettings();
}

void PlaylistView::onSettingsChanged(QString setting)
{
    if ( setting == "selectedHeaders" )
    {
        Core::SettingsModule* settings = Core::ICore::settingsManager()->getModule("org.safri.playlist");
        QString selectedHeaders = settings->getSetting("selectedHeaders").toString();

        setSectionVisibilityFromSettings(selectedHeaders);
    }
}
