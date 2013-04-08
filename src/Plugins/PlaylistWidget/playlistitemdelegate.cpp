#include "playlistitemdelegate.h"
#include "icore.h"
#include <QDebug>
#include <QPainter>

PlaylistItemDelegate::PlaylistItemDelegate(PlaylistWidget* plWidget, QObject *parent) :
    QItemDelegate(parent), plWidget(plWidget)
{
  playbackConntroller = Core::ICore::playbackController();
}

void PlaylistItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(plWidget->isCurrentPlayingPlaylist() && index.data(Qt::UserRole).toBool())
    {

        painter->fillRect(option.rect,QColor("#E1DBBD") );
    }
    QItemDelegate::paint(painter, option, index);
}

