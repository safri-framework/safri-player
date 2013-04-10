#ifndef IMEDIACOLLECTIONSTORAGEFACTORY_H
#define IMEDIACOLLECTIONSTORAGEFACTORY_H

#include <QObject>
#include <QString>
#include "CorePlugin_global.h"

namespace Core
{
    class IMediaCollectionStorgae;

    class COREPLUGINSHARED_EXPORT IMediaCollectionStorageFactory : public QObject
    {
        Q_OBJECT
        public:

            explicit IMediaCollectionStorageFactory(QObject *parent = 0);

            virtual QString                     getStorageType() = 0;
            virtual IMediaCollectionStorgae*    createMediaCollectionStorage(QUrl url) = 0;
    };
}

#endif // IMEDIACOLLECTIONSTORAGEFACTORY_H
