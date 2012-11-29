#include "audiocollectionbuilder.h"

AudioCollectionBuilder::AudioCollectionBuilder(QObject *parent) :
    QObject(parent)
{
}

IMediaCollection *AudioCollectionBuilder::buildMediaCollection(IStorageAdapter *storageAdapter, MetaInfoAdaper* adapter)
{


    //QString name = metaInfoAdapter->getDBName();
    QString name;

    if(!metaInfoAdapter)
    {
        name = "SafriInitialCollection";
    }
    else
    {

    }

    currentAudioCollection = new AudioCollection(name);





}

void AudioCollectionBuilder::storeMediaCollection(IMediaCollection *mediaCollection, IStorageAdapter *storageAdapter)
{
}

void AudioCollectionBuilder::buildGenres(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
}

void AudioCollectionBuilder::buildArtists(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
}

void AudioCollectionBuilder::buildAlbums(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
}

void AudioCollectionBuilder::buildSongs(IStorageAdapter *storageAdapter, AudioCollection *mediaCollection)
{
}
