#ifndef SPOTIFYPLUGIN_H
#define SPOTIFYPLUGIN_H
#include "spotifyplugin_global.h"
#include "iplugin.h"

class SPOTIFYPLUGINSHARED_EXPORT SpotifyPlugin : public PluginSystem::IPlugin
{    
    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)
    Q_PLUGIN_METADATA(IID "SpotifyPlugin" FILE "spotifyplugin.json")

public:
    SpotifyPlugin();
    bool initialize(QStringList &arguments);
};

#endif // SPOTIFYPLUGIN_H
