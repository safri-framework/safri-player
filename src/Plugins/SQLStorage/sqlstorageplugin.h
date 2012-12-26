#ifndef SQLSTORAGEPLUGIN_H
#define SQLSTORAGEPLUGIN_H

#include "SQLStorage_global.h"
#include "iplugin.h"

namespace Plugins
{
    class SQLSTORAGESHARED_EXPORT SQLStoragePlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        public:

            SQLStoragePlugin();
            bool initialize(QStringList &arguments);
    };
}

#endif // SQLSTORAGEPLUGIN_H
