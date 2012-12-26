#include "audiocollectionplugin.h"
#include "audiocollectionbuilder.h"

using namespace Plugins;

AudioCollectionPlugin::AudioCollectionPlugin()
{
}

bool AudioCollectionPlugin::initialize(QStringList &arguments)
{
    AudioCollectionBuilder* collectionBuilder = new AudioCollectionBuilder();
    addObject(collectionBuilder);
}

Q_EXPORT_PLUGIN2(AudioCollectionPlugin, AudioCollectionPlugin)
