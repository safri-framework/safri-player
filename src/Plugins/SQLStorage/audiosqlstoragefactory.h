#ifndef SQLSTORAGEFACTORY_H
#define SQLSTORAGEFACTORY_H

#include "SQLStorage_global.h"
#include "Interfaces/istorageadapterfactory.h"

class SQLSTORAGESHARED_EXPORT AudioSQLStorageFactory : public Core::IStorageAdapterFactory
{
    public:

        AudioSQLStorageFactory(QObject *parent = 0);

        virtual QString getStorageType();
        virtual QString getCollectionType();
        virtual Core::IStorageAdapter* createStorageAdapter(QUrl storagePath);
};

#endif // SQLSTORAGEFACTORY_H
