#ifndef ARTISTSONGITEMTYPE_H
#define ARTISTSONGITEMTYPE_H

#include <QObject>


#include "../../CorePlugin_global.h"
#include "../../Interfaces/itreeitemtype.h"

namespace Core
{
    class COREPLUGINSHARED_EXPORT ArtistSongItemType : public ITreeItemType
    {
        public:
            ArtistSongItemType();

            QString getTypeName();
            QString getNodeName(Song* song);
            DataItem* getNodeDataItem(Song *song);
            QString getHash(Song* song);
    };
}

#endif // ARTISTSONGITEMTYPE_H
