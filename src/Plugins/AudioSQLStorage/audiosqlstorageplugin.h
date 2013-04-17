#ifndef AUDIOSQLSTORAGEPLUGIN_H
#define AUDIOSQLSTORAGEPLUGIN_H

#include "AudioSQLStorage_global.h"
#include "iplugin.h"

namespace Plugins
{
    class AUDIOSQLSTORAGESHARED_EXPORT AudioSQLStoragePlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "AudioSQLStoragePlugin" FILE "audiosqlstorageplugin.json")

        public:

            AudioSQLStoragePlugin();
            bool initialize(QStringList &arguments);
    };
}
#endif // AUDIOSQLSTORAGEPLUGIN_H
