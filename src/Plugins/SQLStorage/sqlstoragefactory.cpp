#include "sqlstoragefactory.h"
#include "sqlstorageadapter.h"

AudioSQLStorageFactory::AudioSQLStorageFactory(QObject *parent)
    : IStorageAdapterFactory(parent)
{
}

QString AudioSQLStorageFactory::getStorageType()
{
    return STORAGE_TYPE;
}

QString AudioSQLStorageFactory::getCollectionType()
{
    return AUDIO_COLLECTION_TYPE;
}

Core::IStorageAdapter *AudioSQLStorageFactory::createStorageAdapter(QUrl storagePath)
{
    return new SQLStorageAdapter(storagePath);
}
