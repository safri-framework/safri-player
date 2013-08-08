#ifndef SAFRI3SKIN_H
#define SAFRI3SKIN_H

#include "Interfaces/ISafriSkin.h"
#include <QMap>

class Safri3Skin : public Core::ISafriSkin
{
    Q_OBJECT
    public:

        Safri3Skin();
        ~Safri3Skin();

        QString                 getStyleSheet();
        QStyledItemDelegate*    getSongTreeItemDelegate();
        QStyledItemDelegate*    getPlaylistItemDelegate();
        void                    paintCurrentSongRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void                    paintRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        QIcon*                  getIcon(QString itemType);
        QString                 getName();
        QSize                   playlistRowSizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
        void                    paintTreeItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        virtual QSize            treeViewSizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;


    private:

        QString style;
        QMap<QString, QIcon*> iconMap;
};

#endif // SAFRI3SKIN_H
