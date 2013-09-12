#ifndef ALBUMTREEITEMTYPE_H
#define ALBUMTREEITEMTYPE_H

#include "CorePlugin_global.h"
#include "Interfaces/ITreeItemType.h"

namespace Core
{
    /**
        \brief  ItemType that generates the node name for the album of a song.

        This implementation of the ITreeItemType interface generates the node name
        for the album of a song.
      */
    class COREPLUGINSHARED_EXPORT AlbumItemType : public ITreeItemType
    {
        public:
            AlbumItemType();
            QString getTypeName();
            QString getNodeName(Song* song);
            DataItem* getNodeDataItem(Song *song);
            QString getHash(Song* song);
    };
}

#endif // ALBUMTREEITEMTYPE_H
