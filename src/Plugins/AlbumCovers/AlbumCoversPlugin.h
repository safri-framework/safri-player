#ifndef ALBUMCOVERSPLUGIN_H
#define ALBUMCOVERSPLUGIN_H

#include "albumcovers_global.h"
#include "iplugin.h"

class ALBUMCOVERSSHARED_EXPORT AlbumCoversPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)
    Q_PLUGIN_METADATA(IID "AlbumCoversPlugin" FILE "albumcovers.json")
    
public:
    AlbumCoversPlugin();
    bool initialize(QStringList &arguments);
};

#endif // ALBUMCOVERSPLUGIN_H
