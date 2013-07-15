#ifndef ITREEITEM_H
#define ITREEITEM_H

#include "CorePlugin_global.h"

#include <QObject>
#include <QString>

namespace Core
{

    /**
     * @brief The ITreeItem class is a basic interface for items in a tree data structure.
     */
    class COREPLUGINSHARED_EXPORT ITreeItem : public QObject
    {
        Q_OBJECT
        public:

            explicit ITreeItem(QObject *parent = 0);

            /**
             * @return the parent item
             */
            virtual ITreeItem*      getParent() = 0;
            virtual void            setParent(ITreeItem* sParent) = 0;

            /**
             * @return the number of tree childs
             */
            virtual int             getChildCount() = 0;

            /**
             * @return the child item at the given index
             */
            virtual ITreeItem*      getChildAt(int index) = 0;

            /**
             * @return the index of the given child
             */
            virtual int             getIndexOfChild(ITreeItem* child) = 0;

            virtual void            addChild(ITreeItem* child) = 0;
            virtual void            removeChild(ITreeItem* child) = 0;

        signals:

            /**
             * @brief this signal is emitted when the item was assigned
             *        to a new parent item.
             * @param the new parent of the sender item
             */
            void parentChanged(ITreeItem* newParent);

            /**
             * @brief this signal is emitted when a new child was added
             * @param the new added child
             */
            void childAdded(ITreeItem* newChild);

            /**
             * @brief this signal is emitted when a child was removed
             * @param the removed child
             */
            void childRemoved(ITreeItem* removedChild);

            /**
             * @brief this signal is emitted when the payload data has changed
             */
            void dataChanged();
    };

}


#endif // ITREEITEM_H
