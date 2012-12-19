#ifndef DECADETREEITEMTYPE_H
#define DECADETREEITEMTYPE_H

#include "../../CorePlugin_global.h"
#include "../../Interfaces/itreeitemtype.h"

namespace Core
{
    /**
        \brief  ItemType that generates the node name for the decade of a song.

        This implementation of the ITreeItemType interface generates the node name
        for the decade of a song. As there is no essential DataItem for decades the
        getNodeDTO function only returns 0.
      */
    class COREPLUGINSHARED_EXPORT DecadeItemType : public ITreeItemType
    {
        public:
            DecadeItemType();
            QString getTypeName();
            QString getNodeName(Song* song);
            DataItem* getNodeDataItem(Song *song);
            QString getHash(Song* song);
    };

}

#endif // DECADETREEITEMTYPE_H
