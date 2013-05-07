#ifndef LASTFMINFORESOLVERPLUGIN_H
#define LASTFMINFORESOLVERPLUGIN_H

#include <QObject>
#include "lastfminforesolver_global.h"
#include "iplugin.h"

namespace Plugins
{
    class LASTFMINFORESOLVERSHARED_EXPORT LastFMInfoResolverPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "LastFMInfoResolverPlugin" FILE "lastfminforesolverplugin.json")

        public:

            LastFMInfoResolverPlugin();

            bool initialize(QStringList &arguments);
    };
}


#endif // LASTFMINFORESOLVERPLUGIN_H
