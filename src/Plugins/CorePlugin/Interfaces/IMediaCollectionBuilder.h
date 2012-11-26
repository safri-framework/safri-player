#ifndef IMEDIACOLLECTIONBUILDER_H
#define IMEDIACOLLECTIONBUILDER_H

#include "../CorePlugin_global.h"
#include "IStorageAdapter.h"

namespace Core
{
    class IMediaCollection;

    class COREPLUGINSHARED_EXPORT IMediaCollectionBuilder
    {
        public:

            virtual ~IMediaCollectionBuilder() {}

            IMediaCollection* getMediaCollection(IDataItemLoader* itemLoader) = 0;
    };
}

#endif // IMEDIACOLLECTIONBUILDER_H
