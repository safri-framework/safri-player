#include "Safri3Skin.h"
#include <QFile>
#include <QSize>
#include <QPainter>
#include <QtWidgets/qstyleoption.h>

Safri3Skin::Safri3Skin()
{
    QFile file;
    file.setFileName(":stylesheet/stylesheet.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String( file.readAll() );
    file.close();
    style = styleSheet;
}

QString Safri3Skin::getStyleSheet()
{
    return style;
}

QStyledItemDelegate *Safri3Skin::getSongTreeItemDelegate()
{
    return 0;
}

QStyledItemDelegate *Safri3Skin::getPlaylistItemDelegate()
{
    return 0;
}

void Safri3Skin::paintCurrentSongRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 0)
    {
        painter->drawPixmap(option.rect.x()+5, option.rect.y() + 1, 13, 13, QPixmap(":images/ressources/play_icon.png"));
    }
    Q_UNUSED(option)
    Q_UNUSED(index)
}

void Safri3Skin::paintRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(index)
}

QIcon *Safri3Skin::getIcon(QString itemType)
{
    Q_UNUSED(itemType)
    return 0;
}

QString Safri3Skin::getName()
{
    return "Safri 3 Skin";
}

QSize Safri3Skin::playlistRowSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return QSize(option.rect.width(), 20);
}

void Safri3Skin::paintTreeItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(index)
}

QSize Safri3Skin::treeViewSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}
