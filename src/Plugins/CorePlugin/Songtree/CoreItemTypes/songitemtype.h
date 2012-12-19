#ifndef SONGTREEITEMTYPE_H
#define SONGTREEITEMTYPE_H

#include "../../CorePlugin_global.h"
#include "../../CoreData/song.h"
#include "../../Interfaces/itreeitemtype.h"

namespace Core
{
    /**
        \brief  ItemType that generates the node name for the title of a song.

        This implementation of the ITreeItemType interface generates the node name
        for the title of a song.
      */
    class COREPLUGINSHARED_EXPORT SongItemType : public ITreeItemType
    {

        public:
            SongItemType();

            QString getTypeName();
            QString getNodeName(Song* song);
            BaseDTO* getNodeDTO(Song *song);
            QString getHash(Song* song);
    };
}

#endif // SONGTREEITEMTYPE_H
