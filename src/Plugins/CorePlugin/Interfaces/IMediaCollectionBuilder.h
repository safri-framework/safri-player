#ifndef IMEDIACOLLECTIONBUILDER_H
#define IMEDIACOLLECTIONBUILDER_H

#include <QObject>
#include "../CorePlugin_global.h"
#include "IStorageAdapter.h"
#include "IMediaCollection.h"

namespace Core
{
    class IMediaCollection;
    class MetaInfo;

    class COREPLUGINSHARED_EXPORT IMediaCollectionBuilder : public QObject
    {
        Q_OBJECT
        public:

            IMediaCollectionBuilder(QObject *parent);
            virtual ~IMediaCollectionBuilder();

            virtual IMediaCollection* buildMediaCollection(IStorageAdapter* storageAdapter, MetaInfo* metaInfoAdapter = 0) = 0;
            virtual void storeMediaCollection(IMediaCollection* mediaCollection, IStorageAdapter* storageAdapter) = 0;
            virtual QString getCollectionType() = 0;
    };
}

Q_DECLARE_INTERFACE(Core::IMediaCollectionBuilder, "Core::IMediaCollectionBuilder")

#endif // IMEDIACOLLECTIONBUILDER_H
