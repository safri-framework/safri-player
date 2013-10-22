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

        void setSectionResizable(int logicalIndex, bool resizable);
        bool isSectionResizable(int logicalIndex);

    signals:

        void sectionVisibilityChanged(int logicalIndex);

    public slots:

        void setSectionManualResizing();
        void setSectionAutoResizeAvailableSpace();
        void setSectionAutoResizeToContent();

    private slots:

        void onContextMenuRequested(QPoint pos);
        void toggleSectionVisibility(int section);

    private:

        QBitArray sectionHideable;
        QBitArray sectionResizable;
};

#endif // PLAYLISTHEADERVIEW_H
