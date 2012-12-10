#ifndef AUDIOCOLLECTIONBUILDER_H
#define AUDIOCOLLECTIONBUILDER_H

#include <QObject>
#include "Interfaces/IMediaCollectionBuilder.h"
#include "audiocollection.h"
#include "Interfaces/IStorageAdapter.h"
#include <QMultiMap>

using namespace Core;

class AudioCollectionBuilder : public IMediaCollectionBuilder
{
    public:

        explicit AudioCollectionBuilder(QObject *parent = 0);
        IMediaCollection* buildMediaCollection(IStorageAdapter* storageAdapter, MetaInfo* metaInfoAdapter = 0);
        void storeMediaCollection(IMediaCollection* mediaCollection, IStorageAdapter* storageAdapter);

    private:

        void buildGenres(IStorageAdapter* storageAdapter, AudioCollection* mediaCollection);
        void buildArtists(IStorageAdapter* storageAdapter, AudioCollection* mediaCollection);
        void buildAlbums(IStorageAdapter* storageAdapter, AudioCollection* mediaCollection);
        void buildSongs(IStorageAdapter* storageAdapter, AudioCollection* mediaCollection);

        QMultiMap<int, int> loadArtistToAlbumMap(IStorageAdapter* storageAdapter);
};

#endif // AUDIOCOLLECTIONBUILDER_H
