#ifndef AUDIOCOLLECTIONPLUGIN_H
#define AUDIOCOLLECTIONPLUGIN_H

#include "AudioCollection_global.h"
#include "iplugin.h"

class AUDIOCOLLECTIONSHARED_EXPORT AudioCollectionPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_INTERFACES(PluginSystem::IPlugin)
    public:

        AudioCollectionPlugin();
        bool initialize(QStringList &arguments);
};

#endif // AUDIOCOLLECTIONPLUGIN_H
