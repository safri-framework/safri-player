#ifndef ISAFRISKIN_H
#define ISAFRISKIN_H

#include "../CorePlugin_global.h"
#include <QObject>

class QStyledItemDelegate;
class QIcon;
class QPainter;
class QModelIndex;
class QStyleOptionViewItem;

namespace Core
{
    class COREPLUGINSHARED_EXPORT ISafriSkin : public QObject
    {
        Q_OBJECT
    public:
        explicit ISafriSkin(QObject *parent = 0);
        virtual ~ISafriSkin();
        virtual QString getStyleSheet() = 0;
        virtual QStyledItemDelegate* getSongTreeItemDelegate() = 0;
        virtual QStyledItemDelegate* getPlaylistItemDelegate() = 0;
        virtual QIcon* getIcon(QString itemType) = 0;
        virtual QString getName() = 0;
        virtual void paintCurrentSongRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const = 0;
        virtual void paintRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const = 0;
        virtual QSize playlistRowSizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const = 0;

    signals:


    public slots:

    };
}
#endif // ISAFRISKIN_H
