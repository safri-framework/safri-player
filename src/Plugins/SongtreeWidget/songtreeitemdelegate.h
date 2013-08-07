#ifndef SONGTREEITEMDELEGATE_H
#define SONGTREEITEMDELEGATE_H

#include <QItemDelegate>
#include "../CorePlugin/iplaybackcontroller.h"
#include "Interfaces/ISafriSkin.h"

class SongTreeItemDelegate : public QItemDelegate
{
    Q_OBJECT



public:
    explicit SongTreeItemDelegate(QObject *parent = 0);
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

private:
    Core::IPlaybackController* playbackConntroller;
    Core::ISafriSkin* skin;

};

#endif // SONGTREEITEMDELEGATE_H
