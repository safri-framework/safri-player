#ifndef IMEDIACOLLECTIONSTORAGE_H
#define IMEDIACOLLECTIONSTORAGE_H

#include <QObject>
#include <QString>
#include "CorePlugin_global.h"

namespace Core
{
    class IMediaCollection;

    /**
     * @brief   The IMediaCollectionStorage provides an interface to
     *          load and save MediaCollections.
     */
    class COREPLUGINSHARED_EXPORT IMediaCollectionStorage : public QObject
    {
        Q_OBJECT
        public:

            explicit IMediaCollectionStorage(QObject *parent = 0);

            /**
             * @brief   loadMediaCollection loads a MediaCollection from an url.
             *          Note, that the returned MediaCollection doesn't need to
             *          be necessarily completely loaded already.
             *
             * @return the MediaCollection that was load.
             */
            virtual IMediaCollection*       loadMediaCollection() = 0;

            /**
             * @brief   saveMediaCollection saves the given MediaCollection to
             *          an url.
             *
             * @param collection the MediaCollection to save
             * @return  success of operation
             */
            virtual bool                    saveMediaCollection(IMediaCollection    *collection) = 0;

            /**
             * @brief getStorageType returns the storage type that is supported.
             * @return storage type string
             */
            virtual QString                 getStorageType() = 0;

    };
}

#endif // IMEDIACOLLECTIONSTORAGE_H
