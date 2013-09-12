#ifndef SONGTREEITEM_H
#define SONGTREEITEM_H

#include <QList>
#include <QMap>
#include <QRegExp>

#include "CorePlugin_global.h"
#include "CoreData/DataItem.h"
#include "Interfaces/ITreeItemType.h"
#include "ChangedFlags.h"
#include "CoreData/Item.h"
#include "CoreData/Media.h"

//#define DEBUG

namespace Core
{
    class SongTree;

    class COREPLUGINSHARED_EXPORT SongTreeItem : public Item
    {
        Q_OBJECT
        public:

            /**
                \brief Kind of copy constructor: apply most of the data from the sample item
                       (execpt the childs) but set different parents
            */
            SongTreeItem(SongTreeItem* sample, SongTreeItem* parentItem, QObject *parent);

            SongTreeItem(ITreeItemType* type, int level, QList<ITreeItemType*>* hierarchy, SongTreeItem* parentItem, Song* song, SongTree* songTree, QObject *parent);
            SongTreeItem(QList<ITreeItemType*>* hierarchy, SongTree* songTree, QObject *parent);

            ~SongTreeItem();

            /**
                \returns    returns true if one of the child items contains the given regEx.
            */
            bool subTreeContains(QRegExp exp);

            /**
                \returns    returns true if one of the ancestors contains the given regEx.
            */
            bool ancestorsContains(QRegExp exp);

            /**
                \returns    list of song leaves under this node
            */
            QList<Song*> getSongs();

            /**
                \returns    the item's location within its parent's list of items
            */
            int getRow();

            /**
                \param      index of the child
                \returns    the child at the specified index
            */
            SongTreeItem* getChild(int index) const;

            /**
                \brief      Recursively removes this item from the tree.

                This function removes the item from the parent item and propagates the
                removal up to the root, when there are no more childs in the parent item.

                \param      Sender item of the remove message. Set this to 0 when invoke
                            from outside the tree.
            */
            void remove(SongTreeItem* sender = 0);

            /**
                \brief      Recursively removes this item from the tree with all child Items.

                This function removes the item from the parent item and propagates the
                removal down to all child items.

            */
            void removeSubtree();

            /**
                \brief      Checks if the other tree item is involved in the
                            parent relation of this tree item.

                \param      the other tree item
                \returns    true if the other item is involved in the
                            parent relation of this tree item
            */
            bool hasParentRelation(SongTreeItem* other);

            /**
                \brief      Returns the child item corresponding to the song or
                            if there is no such item insert it.

                \param      the song for wich the child should be returned
                \returns    the corresponding item
            */
            SongTreeItem* getOrInsertChildItem(Song* song);

            /**
                \brief      Returns the child item corresponding to sample item or
                            if there is no such item insert it.

                \param      the "sample item" for wich the child should be returned
                \returns    the corresponding item
            */
            SongTreeItem* getOrInsertChildItem(SongTreeItem* sampleItem);

            /**
                \brief      Moves the SongTreeItem to another parent.

                \param      the destination, which will become the new parent
            */
            void moveToParent(SongTreeItem* destination);

            QList<SongTreeItem*> getChilds() const;

            void print();
            QString getName();
            void addSong(Song* song);
            QString getTypeName();
            void setDataItemPtr(DataItem* dataItemPtr);
            DataItem* getDataItemPtr();
            int getTreeLevel();
            int getNumberOfChilds() const;
            SongTreeItem* getParentItem() const;
            QList<Media*> getMedia();

    #ifdef DEBUG
            long ID;
            static long idCount;
    #endif

        private:

            SongTreeItem* parentItem;
            QList<SongTreeItem*>* childs;
            QMap<QString, SongTreeItem*>* childMap;

            DataItem* dataItemPtr;
            QString name;

            ITreeItemType* type;
            int level;

            /**
                \brief      Adapts the data from parent up the tree to the source item.
                            (Modify the songs from source according to the tree.)
                \param      the source item, which was moved
                \param      holds the flags which data was changed
            */
            void adaptParentDataToSource(SongTreeItem* source, ChangedFlags &flags);

            QList<ITreeItemType*>* hierarchy;

            /**
              Each SongTreeItem stores a pointer to the overall SongTree object. So
              signaling new inserted items can be passed directly to the tree object
              instead of passing it all the way along the path to the root.
            */
            SongTree* songTree;

            bool useHash();

            bool checkForEqualCostumType(SongTreeItem *destination);

            QString hash;
    };
}

#endif

