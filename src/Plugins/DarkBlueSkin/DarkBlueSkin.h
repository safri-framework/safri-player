#ifndef DARKBLUESKIN_H
#define DARKBLUESKIN_H

#include "Interfaces/ISafriSkin.h"
#include <QModelIndex>
#include <QtWidgets/qstyleoption.h>
#include <QPainter>

using namespace  Core;

class DarkBlueSkin : public ISafriSkin
{
public:
    DarkBlueSkin();
    ~DarkBlueSkin();
    QString getStyleSheet();
    QStyledItemDelegate* getSongTreeItemDelegate();
    QStyledItemDelegate* getPlaylistItemDelegate();
    void paintCurrentSongRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QIcon* getIcon(QString itemType);
    QString getName();
    QSize playlistRowSizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;


private:
    QString style;
    QMap<QString, QIcon*> iconMap;
};

#endif // DARKBLUESKIN_H
