#ifndef BASICTREEITEM_H
#define BASICTREEITEM_H

#include "Interfaces/ITreeItem.h"

#include <QList>

namespace Core
{
    /**
     * @brief The BasicTreeItem class is a basic implementation of a tree item.
     *
     * This basic implementation of a tree item doesn't provide an attribute
     * for the data payload. As it's subclassed from QObject data payload can be
     * added as Qt propteries or if you need any particular payload you can subclass
     * this basic implementation.
     */
    class COREPLUGINSHARED_EXPORT BasicTreeItem : public ITreeItem
    {
        Q_OBJECT
        public:

            explicit BasicTreeItem(ITreeItem *parentItem = 0, QObject *parent = 0);

            virtual ITreeItem*      getParent();
            virtual void            setParent(ITreeItem* sParent);

            virtual int             getChildCount();
            virtual ITreeItem*      getChildAt(int index);
            virtual int             getIndexOfChild(ITreeItem* child);

            virtual void            addChild(ITreeItem* child);
            virtual void            removeChild(ITreeItem* child);

        protected:

            ITreeItem* parentItem;
            QList<ITreeItem*> childs;
    };

}

#endif // BASICTREEITEM_H
