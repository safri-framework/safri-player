#include "sqlstoragefactory.h"
#include "sqlstorageadapter.h"

SQLStorageFactory::SQLStorageFactory(QObject *parent)
    : IStorageAdapterFactory(parent)
{
}

QString SQLStorageFactory::getStorageType()
{
    return STORAGE_TYPE;
}

Core::IStorageAdapter *SQLStorageFactory::createStorageAdapter(QUrl storagePath)
{
    return new SQLStorageAdapter(storagePath);
}
