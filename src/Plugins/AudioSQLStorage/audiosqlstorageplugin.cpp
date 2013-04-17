#include "audiosqlstorageplugin.h"
#include "audiosqlstoragefactory.h"

using namespace Plugins;

AudioSQLStoragePlugin::AudioSQLStoragePlugin()
{
}


bool AudioSQLStoragePlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    AudioSQLStorageFactory *factory = new AudioSQLStorageFactory(this);

    addObject(factory);

    return true;
}
