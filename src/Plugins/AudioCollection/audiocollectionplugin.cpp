#include "audiocollectionplugin.h"
#include "audiocollectionbuilder.h"
#include "audiocollectionfactory.h"

using namespace Plugins;

AudioCollectionPlugin::AudioCollectionPlugin()
{
}

bool AudioCollectionPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    AudioCollectionBuilder* collectionBuilder = new AudioCollectionBuilder();
    AudioCollectionFactory* collectionFactory = new AudioCollectionFactory(this);

    addObject(collectionBuilder);
    addObject(collectionFactory);

    return true;
}

