#ifndef SONGTREE_H
#define SONGTREE_H

#include "../Interfaces/itreeitemtype.h"

class SongTreeItem;

class SongTree : public QObject
{
    Q_OBJECT
    public:

	QList<ITreeItemType*>* hierarchy;
	SongTree(QList<Song*> songs, QList<ITreeItemType*>* hierarchy);

        void print();

        /**
            \returns    the roote SongTreeItem for the song tree
        */
        const SongTreeItem* getRootNode() const;


        /**
            \returns    returns true if there are unsafed changes into the data structure.
        */
        bool isDirty();

    public slots:

        void addSong(Song* song);
        void move(SongTreeItem *source, SongTreeItem *destination);
        void changesSaved();

    signals:


        /**
            \brief  This signal is emmited before an item will be moved.

            \param  the source parent item
            \param  the source row within the source parent
            \param  the destination parent item
            \param  the destination row within the destination parent
        */
        void beginMoveItem(SongTreeItem *srcParent, int srcRow, SongTreeItem *destParent, int destRow);
        void endMoveItem(SongTreeItem *destParent);
        void beginInsertItem(SongTreeItem *parent, int row);
        void endInsertItem();
        void beginRemoveItem(SongTreeItem *parent, int row);
        void endRemoveItem();

    friend class SongTreeItem;

    private:

        void emitBeginMoveItem(SongTreeItem *srcParent, int srcRow, SongTreeItem *destParent, int destRow);
        void emitEndMoveItem(SongTreeItem *destParent);
        void emitBeginInsertItem(SongTreeItem *parent, int row);
        void emitEndInsertItem();
        void emitBeginRemoveItem(SongTreeItem *parent, int row);
        void emitEndRemoveItem();
        bool dirty;
	SongTreeItem* rootNode;
};

#endif

