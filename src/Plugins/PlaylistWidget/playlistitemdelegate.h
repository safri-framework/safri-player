#ifndef PLAYLISTITEMDELEGATE_H
#define PLAYLISTITEMDELEGATE_H

#include <QItemDelegate>
#include "../CorePlugin/iplaybackcontroller.h"
#include "playlistwidget.h"

class PlaylistItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit PlaylistItemDelegate(PlaylistWidget* plWidget, QObject *parent = 0);
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected:


signals:
    
public slots:
    
private:
    Core::IPlaybackController* playbackConntroller;
    PlaylistWidget* plWidget;
};

#endif // PLAYLISTITEMDELEGATE_H
