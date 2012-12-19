#ifndef GENREITEMTYPE_H
#define GENREITEMTYPE_H

#include "../../CorePlugin_global.h"
#include "../../Interfaces/itreeitemtype.h"

/**
    \brief  ItemType that generates the node name for the genre of a song.

    This implementation of the ITreeItemType interface generates the node name
    for the genre of a song.
  */

namespace Core
{
    class COREPLUGINSHARED_EXPORT GenreItemType : public ITreeItemType
    {
    public:
        GenreItemType();

        QString getTypeName();
        QString getNodeName(Song* song);
        BaseDTO* getNodeDTO(Song *song);
        QString getHash(Song* song);
    };
}
#endif // GENREITEMTYPE_H
