#ifndef AUDIOCOLLECTIONBUILDER_H
#define AUDIOCOLLECTIONBUILDER_H

#include <QObject>
#include "Interfaces/IMediaCollectionBuilder.h"
#include "audiocollection.h"
#include "Interfaces/IStorageAdapter.h"


using namespace Core;

class MetaInfoAdaper;
class AudioCollectionBuilder : public QObject, public IMediaCollectionBuilder
{
    Q_OBJECT


public:
    explicit AudioCollectionBuilder(QObject *parent = 0);
    IMediaCollection* buildMediaCollection(IStorageAdapter* storageAdapter, MetaInfoAdaper* adapter = 0);
    void storeMediaCollection(IMediaCollection* mediaCollection, IStorageAdapter* storageAdapter);

private:

    void buildGenres(IStorageAdapter* storageAdapter, AudioCollection* mediaCollection);
    void buildArtists(IStorageAdapter* storageAdapter, AudioCollection* mediaCollection);
    void buildAlbums(IStorageAdapter* storageAdapter, AudioCollection* mediaCollection);
    void buildSongs(IStorageAdapter* storageAdapter, AudioCollection* mediaCollection);

    AudioCollection* currentAudioCollection;
    IStorageAdapter* currentStorageAdapter;
    MetaInfoAdaper* metaInfoAdapter;



signals:
    
public slots:
    
};

#endif // AUDIOCOLLECTIONBUILDER_H
