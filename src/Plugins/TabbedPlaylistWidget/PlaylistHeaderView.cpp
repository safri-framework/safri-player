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
    setStretchLastSection(true);
}

PlaylistHeaderView::~PlaylistHeaderView()
{
}

void PlaylistHeaderView::setModel(QAbstractItemModel *model)
{
    QHeaderView::setModel(model);
    sectionHideable = QBitArray(model->columnCount(), true);
    sectionResizable = QBitArray(model->columnCount(), true);
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

void PlaylistHeaderView::setSectionResizable(int logicalIndex, bool resizable)
{
    if ( logicalIndex < sectionResizable.size() )
    {
        sectionResizable.setBit(logicalIndex, resizable);
        if (resizable)
        {
            setSectionResizeMode(logicalIndex, QHeaderView::Stretch);
        }
        else
        {
            setSectionResizeMode(logicalIndex, QHeaderView::Fixed);
        }
    }
}

bool PlaylistHeaderView::isSectionResizable(int logicalIndex)
{
    if ( logicalIndex < sectionResizable.size() )
    {
        return sectionResizable.testBit(logicalIndex);
    }
    else
    {
        return true;
    }
}

void PlaylistHeaderView::onContextMenuRequested(QPoint pos)
{
    QMenu* contextMenu = new QMenu("Kontext menü", this);
    QMenu* columnSubMenu;
    QMenu* columnResizeSubMenu;
    QAction* selectColumnAction;
    QAction* manualResizeAction;
    QAction* resizeAvailableSpaceAction;
    QAction* resizeToContentAction;
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

    columnResizeSubMenu = contextMenu->addMenu("Spaltengröße anpassen");

    manualResizeAction = new QAction("manuell", columnResizeSubMenu);
    connect(manualResizeAction, SIGNAL( triggered() ), this, SLOT( setSectionManualResizing() ) );

    resizeAvailableSpaceAction = new QAction("nach Fenstergröße", columnResizeSubMenu);
    connect(resizeAvailableSpaceAction, SIGNAL( triggered() ), this, SLOT( setSectionAutoResizeAvailableSpace() ) );

    resizeToContentAction = new QAction("nach Inhalt", columnResizeSubMenu);
    connect(resizeToContentAction, SIGNAL( triggered() ), this, SLOT( setSectionAutoResizeToContent() ) );

    columnResizeSubMenu->addAction(manualResizeAction);
    columnResizeSubMenu->addAction(resizeAvailableSpaceAction);
    columnResizeSubMenu->addAction(resizeToContentAction);

    contextMenu->exec(mapToGlobal(pos));

    QList<QAction*> columnActions = columnSubMenu->actions();

    for (int i = 0; i < columnActions.size(); i++)
    {
        delete columnActions.at(i);
    }

    delete manualResizeAction;

    delete columnSubMenu;
    delete columnResizeSubMenu;

    delete contextMenu;
}

void PlaylistHeaderView::toggleSectionVisibility(int section)
{
    setSectionHidden(section, ! isSectionHidden(section) );
    Q_EMIT sectionVisibilityChanged(section);
}


void PlaylistHeaderView::setSectionManualResizing()
{
    setStretchLastSection(true);
    for (int i = 0; i < count(); i++)
    {
        if ( sectionResizable.testBit(i) )
        {
            setSectionResizeMode(i, QHeaderView::Interactive);
        }
    }
}

void PlaylistHeaderView::setSectionAutoResizeAvailableSpace()
{
    for (int i = 0; i < count(); i++)
    {
        if ( sectionResizable.testBit(i) )
        {
            setSectionResizeMode(i, QHeaderView::Stretch);
        }
    }
    setStretchLastSection(false);
}

void PlaylistHeaderView::setSectionAutoResizeToContent()
{
    for (int i = 0; i < count(); i++)
    {
        if ( sectionResizable.testBit(i) )
        {
            setSectionResizeMode(i, QHeaderView::ResizeToContents);
        }
    }
    setStretchLastSection(false);
}
