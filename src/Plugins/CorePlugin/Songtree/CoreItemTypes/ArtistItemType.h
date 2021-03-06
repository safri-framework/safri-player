#ifndef ARTISTITEMTYPE_H
#define ARTISTITEMTYPE_H

#include "CorePlugin_global.h"
#include "Interfaces/ITreeItemType.h"

namespace Core
{
    /**
        \brief  ItemType that generates the node name for the artist of a song.

        This implementation of the ITreeItemType interface generates the node name
        for the artist of a song.
      */
    class COREPLUGINSHARED_EXPORT ArtistItemType : public ITreeItemType
    {
        public:
            ArtistItemType();
            QString getTypeName();
            QString getNodeName(Song* song);
            DataItem* getNodeDataItem(Song *song);
            QString getHash(Song* song);
    };
}

#endif // ARTISTITEMTYPE_H
