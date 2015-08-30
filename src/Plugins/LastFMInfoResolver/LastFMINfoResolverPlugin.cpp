#include "LastFMINfoResolverPlugin.h"
#include "LastFMInfoResolver.h"
using namespace Plugins;

bool LastFMInfoResolverPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED( arguments )
    addObject(new LastFMInfoResolver());
    return true;
}


LastFMInfoResolverPlugin::LastFMInfoResolverPlugin()
{
}
