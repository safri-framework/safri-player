#ifndef PLAYLISTITEMDELEGATE_H
#define PLAYLISTITEMDELEGATE_H

#include <QItemDelegate>
#include "Interfaces/IPlaybackController.h"
#include "Interfaces/ISafriSkin.h"

class TabbedPlaylistWidget;

class PlaylistItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit PlaylistItemDelegate(TabbedPlaylistWidget* plWidget, QObject *parent = 0);
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
    
private:
    Core::IPlaybackController* playbackConntroller;
    TabbedPlaylistWidget* plWidget;
    Core::ISafriSkin* skin;
};

#endif // PLAYLISTITEMDELEGATE_H
