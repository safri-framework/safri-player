#ifndef SQLSTORAGEFACTORY_H
#define SQLSTORAGEFACTORY_H

#include "SQLStorage_global.h"
#include "Interfaces/istorageadapterfactory.h"

class SQLSTORAGESHARED_EXPORT SQLStorageFactory : public Core::IStorageAdapterFactory
{
    public:
        SQLStorageFactory(QObject *parent = 0);

        virtual QString getStorageType();
        virtual Core::IStorageAdapter* createStorageAdapter(QUrl storagePath);
};

#endif // SQLSTORAGEFACTORY_H
