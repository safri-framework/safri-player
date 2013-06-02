#include "audiocollectionfactory.h"
#include "audiocollection.h"

AudioCollectionFactory::AudioCollectionFactory(QObject *parent) :
    IMediaCollectionFactory(parent)
{
}

QString AudioCollectionFactory::getCollectionType()
{
    return "org.safri.collection.audio";
}

IMediaCollection* AudioCollectionFactory::createMediaCollection(QString name, QUrl url)
{
    return new AudioCollection(name, url);
}
