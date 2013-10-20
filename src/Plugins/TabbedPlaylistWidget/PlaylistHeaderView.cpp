#include "PlaylistHeaderView.h"
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QSignalMapper>

PlaylistHeaderView::PlaylistHeaderView(QWidget *parent) :
    QHeaderView(Qt::Horizontal, parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect( this, SIGNAL( customContextMenuRequested(QPoint) ), this, SLOT( onContextMenuRequested(QPoint) ) );

    setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

PlaylistHeaderView::~PlaylistHeaderView()
{
}

void PlaylistHeaderView::setModel(QAbstractItemModel *model)
{
    QHeaderView::setModel(model);
    sectionHideable = QBitArray(model->columnCount(), true);
}

void PlaylistHeaderView::setSectionHideable(int logicalIndex, bool hideable)
{
    if ( logicalIndex < sectionHideable.size() )
    {
        sectionHideable.setBit(logicalIndex, hideable);
    }
}

bool PlaylistHeaderView::isSectionHideable(int logicalIndex)
{
    if ( logicalIndex < sectionHideable.size() )
    {
        return sectionHideable.testBit(logicalIndex);
    }
    else
    {
        return false;
    }
}

void PlaylistHeaderView::onContextMenuRequested(QPoint pos)
{
    QMenu* contextMenu = new QMenu("Kontext menü", this);
    QMenu* columnSubMenu;
    QAction* selectColumnAction;
    QSignalMapper selectColumnSignalMapper;

    columnSubMenu = contextMenu->addMenu("Spalten");

    for (int i = 0; i < count(); i++)
    {
        if ( sectionHideable.testBit(i) )
        {
            selectColumnAction = new QAction( model()->headerData(i, Qt::Horizontal).toString() , columnSubMenu);

            selectColumnAction->setCheckable(true);
            selectColumnAction->setChecked( !isSectionHidden(i) );

            connect( selectColumnAction, SIGNAL( triggered() ), &selectColumnSignalMapper, SLOT( map() ) );
            selectColumnSignalMapper.setMapping(selectColumnAction, i);

            columnSubMenu->addAction(selectColumnAction);
        }
    }

    connect(&selectColumnSignalMapper, SIGNAL( mapped(int) ), this, SLOT( toggleSectionVisibility(int) ) );

    contextMenu->exec(mapToGlobal(pos));

    QList<QAction*> columnActions = columnSubMenu->actions();

    for (int i = 0; i < columnActions.size(); i++)
    {
        delete columnActions.at(i);
    }

    delete columnSubMenu;
    delete contextMenu;
}

void PlaylistHeaderView::toggleSectionVisibility(int section)
{
    setSectionHidden(section, ! isSectionHidden(section) );
    Q_EMIT sectionVisibilityChanged(section);
}
