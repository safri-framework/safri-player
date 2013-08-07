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

    QSize defaultSize = QItemDelegate::sizeHint(option, index);
    if(skin)
    {
        QSize skinSize =  skin->treeViewSizeHint(option, index);

        if(skinSize.height() > defaultSize.height())
            return skinSize;

    }


    return defaultSize;
}
