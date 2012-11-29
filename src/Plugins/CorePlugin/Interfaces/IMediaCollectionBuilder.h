#ifndef IMEDIACOLLECTIONBUILDER_H
#define IMEDIACOLLECTIONBUILDER_H

#include "../CorePlugin_global.h"
#include "IStorageAdapter.h"
#include "IMediaCollection.h"


namespace Core
{
    class IMediaCollection;

    class COREPLUGINSHARED_EXPORT IMediaCollectionBuilder
    {
        public:

            virtual ~IMediaCollectionBuilder();

            virtual IMediaCollection* buildMediaCollection(IStorageAdapter* storageAdapter) = 0;
            virtual void storeMediaCollection(IMediaCollection* mediaCollection, IStorageAdapter* storageAdapter) = 0;





    };
}



Q_DECLARE_INTERFACE(Core::IMediaCollectionBuilder, "Core::IMediaCollectionBuilder")


#endif // IMEDIACOLLECTIONBUILDER_H
