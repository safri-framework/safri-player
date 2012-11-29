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

            IMediaCollection* buildMediaCollection(IStorageAdapter* storageAdapter) = 0;
            void storeMediaCollection(IMediaCollection* mediaCollection, IStorageAdapter* storageAdapter) = 0;
    };
}

#endif // IMEDIACOLLECTIONBUILDER_H
