#include "songtreeitemdelegate.h"
#include "icore.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOptionViewItem>

SongTreeItemDelegate::SongTreeItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
    skin = Core::ICore::instance()->skin();
}

void SongTreeItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(skin)
    {
        skin->paintTreeItem(painter, option, index);
    }

    QItemDelegate::paint(painter, option, index);

}

QSize SongTreeItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(skin)
    {
        return skin->treeViewSizeHint(option, index);
    }
    return QItemDelegate::sizeHint(option, index);
}
