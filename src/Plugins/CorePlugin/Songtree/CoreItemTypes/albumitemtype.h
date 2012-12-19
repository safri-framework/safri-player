#ifndef ALBUMTREEITEMTYPE_H
#define ALBUMTREEITEMTYPE_H

#include "../../Interfaces/itreeitemtype.h"

namespace Core
{
    /**
        \brief  ItemType that generates the node name for the album of a song.

        This implementation of the ITreeItemType interface generates the node name
        for the album of a song.
      */
    class AlbumItemType : public ITreeItemType
    {
        public:
            AlbumItemType();
            QString getTypeName();
            QString getNodeName(Song* song);
            BaseDTO* getNodeDTO(Song *song);
            QString getHash(Song* song);
            QList<QAction*>* getContextMenuActions(SongTreeItem* item);
    };
}

#endif // ALBUMTREEITEMTYPE_H
