#include "audiosqlstoragefactory.h"
#include "audiosqlstorage.h"
#include <QDebug>

AudioSQLStorageFactory::AudioSQLStorageFactory(QObject *parent) :
    IMediaCollectionStorageFactory(parent)
{
}

QString AudioSQLStorageFactory::getStorageType()
{
    return "org.safri.sqlite.audio";
}

Core::IMediaCollectionStorage* AudioSQLStorageFactory::createMediaCollectionStorage(QUrl url)
{
    qDebug() << "AudioSQLStorageFactory::createMediaCollectionStorage()";
    return new AudioSQLStorage(url);
}
