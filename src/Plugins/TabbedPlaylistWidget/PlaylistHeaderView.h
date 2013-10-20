#ifndef PLAYLISTHEADERVIEW_H
#define PLAYLISTHEADERVIEW_H

#include <QHeaderView>
#include <QBitArray>

class PlaylistHeaderView : public QHeaderView
{
    Q_OBJECT
    public:

        explicit PlaylistHeaderView(QWidget *parent = 0);
        ~PlaylistHeaderView();

        virtual void setModel(QAbstractItemModel* model);

        void setSectionHideable(int logicalIndex, bool hideable);
        bool isSectionHideable(int logicalIndex);

    signals:

        void sectionVisibilityChanged(int logicalIndex);

    private slots:

        void onContextMenuRequested(QPoint pos);
        void toggleSectionVisibility(int section);

    private:

        QBitArray sectionHideable;
};

#endif // PLAYLISTHEADERVIEW_H
