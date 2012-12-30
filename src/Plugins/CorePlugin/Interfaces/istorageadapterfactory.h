#ifndef ISTORAGEADAPTERFACTORY_H
#define ISTORAGEADAPTERFACTORY_H

#include <QString>
#include "../CorePlugin_global.h"
#include "IStorageAdapter.h"

namespace Core
{
    class COREPLUGINSHARED_EXPORT IStorageAdapterFactory : public QObject
    {
        Q_OBJECT
        public:
            explicit IStorageAdapterFactory(QObject *parent = 0);

            virtual QString getStorageType() = 0;
            virtual IStorageAdapter* createStorageAdapter(QUrl storagePath) = 0;
    };
}

#endif // ISTORAGEADAPTERFACTORY_H
