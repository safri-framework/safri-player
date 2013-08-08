#include "playlistitemdelegate.h"
#include "icore.h"
#include <QDebug>
#include <QPainter>

PlaylistItemDelegate::PlaylistItemDelegate(PlaylistWidget* plWidget, QObject *parent) :
    QItemDelegate(parent), plWidget(plWidget)
{
    playbackConntroller = Core::ICore::playbackController();
    skin = Core::ICore::skin();
}

void PlaylistItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(skin)
    {
        if(plWidget->isCurrentPlayingPlaylist() && index.data(Qt::UserRole).toBool())
            skin->paintCurrentSongRowInPlaylist(painter, option, index);
        else
            skin->paintRowInPlaylist(painter, option, index);;
    }
    else
    {
        if(plWidget->isCurrentPlayingPlaylist() && index.data(Qt::UserRole).toBool())
        {
            painter->fillRect(option.rect, QColor("#E1DBBD") );
            if(index.column() == 0)
            {
                painter->drawPixmap(option.rect.x()+5, option.rect.y() + 1, 13, 13, QPixmap(":images/ressources/play_icon.png"));
            }
        }
    }
    QItemDelegate::paint(painter, option, index);


}

QSize PlaylistItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(skin)
    {
        return skin->playlistRowSizeHint( option, index);
    }

    if(plWidget->isCurrentPlayingPlaylist() && index.data(Qt::UserRole).toBool())
    {
       // return QSize(option.rect.width(), option.rect.height()+30);
    }
    return QItemDelegate::sizeHint(option, index);
}



