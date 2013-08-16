#ifndef SONGTREE_H
#define SONGTREE_H

#include "../CorePlugin_global.h"
#include <QObject>
#include <QList>
#include "../CoreData/media.h"

namespace Core
{
    class SongTreeItem;
    class ITreeItemType;
    class Song;

    class COREPLUGINSHARED_EXPORT SongTree : public QObject
    {
        friend class SongTreeItem;

        Q_OBJECT
        public:

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
            void addItem(Core::DataItem* item);
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

        private:

            bool dirty;
            SongTreeItem* rootNode;
            QList<ITreeItemType*>* hierarchy;

            void emitBeginMoveItem(SongTreeItem *srcParent, int srcRow, SongTreeItem *destParent, int destRow);
            void emitEndMoveItem(SongTreeItem *destParent);
            void emitBeginInsertItem(SongTreeItem *parent, int row);
            void emitEndInsertItem();
            void emitBeginRemoveItem(SongTreeItem *parent, int row);
            void emitEndRemoveItem();

    };

}

#endif

