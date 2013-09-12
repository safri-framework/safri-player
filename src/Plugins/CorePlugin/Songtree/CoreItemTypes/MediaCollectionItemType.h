#ifndef MEDIACOLLECTIONITEMTYPE_H
#define MEDIACOLLECTIONITEMTYPE_H

#include "CorePlugin_global.h"
#include "Interfaces/ITreeItemType.h"

namespace Core
{
    class COREPLUGINSHARED_EXPORT MediaCollectionItemType : public ITreeItemType
    {
        public:

            MediaCollectionItemType();

            QString getTypeName();
            QString getNodeName(Song* song);
            DataItem* getNodeDataItem(Song *song);
            QString getHash(Song* song);
    };
}
#endif // MEDIACOLLECTIONITEMTYPE_H
