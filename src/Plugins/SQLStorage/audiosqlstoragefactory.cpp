#include "audiosqlstoragefactory.h"
#include "audiosqlstorageadapter.h"

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
    return new AudioSQLStorageAdapter(storagePath);
}
