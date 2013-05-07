#include "LastFMINfoResolverPlugin.h"
#include "LastFMInfoResolver.h"
using namespace Plugins;

bool LastFMInfoResolverPlugin::initialize(QStringList &arguments)
{
    addObject(new LastFMInfoResolver());
    return true;
}


LastFMInfoResolverPlugin::LastFMInfoResolverPlugin()
{
}
