#include "audiocollectionplugin.h"
#include "audiocollectionbuilder.h"

using namespace Plugins;

AudioCollectionPlugin::AudioCollectionPlugin()
{
}

bool AudioCollectionPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    AudioCollectionBuilder* collectionBuilder = new AudioCollectionBuilder();
    addObject(collectionBuilder);

    return true;
}

