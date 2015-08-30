#include "SongTreeView.h"
#include <QDebug>
SongTreeView::SongTreeView(QWidget *parent) :
    QTreeView(parent)
{
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void SongTreeView::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED( event )
    qDebug()<<"FOCUS OUT";
    this->selectionModel()->clearSelection();
}
