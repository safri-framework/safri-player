#ifndef TRACKSONGITEMTYPE_H
#define TRACKSONGITEMTYPE_H

#include "../../CorePlugin_global.h"
#include "../../Interfaces/itreeitemtype.h"

/**
    \brief  ItemType that generates the node name for the title of a song
            with the leading track number.

    This implementation of the ITreeItemType interface generates the node name
    for the title of a song with the leading track number.
  */


namespace Core
{
    class COREPLUGINSHARED_EXPORT TrackSongItemType : public ITreeItemType
    {
        public:

            TrackSongItemType();

            QString getTypeName();
            QString getNodeName(Song* song);
            BaseDTO* getNodeDTO(Song *song);
            QString getHash(Song* song);
    };
}

#endif // TRACKSONGITEMTYPE_H
