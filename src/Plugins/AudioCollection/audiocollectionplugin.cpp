#include "audiocollectionplugin.h"
#include "audiocollectionfactory.h"

using namespace Plugins;

AudioCollectionPlugin::AudioCollectionPlugin()
{
}

bool AudioCollectionPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    AudioCollectionFactory* collectionFactory = new AudioCollectionFactory(this);

    addObject(collectionFactory);

    return true;
}

