#ifndef SAFRIMOBILEGUIQML_H
#define SAFRIMOBILEGUIQML_H

#include "SafriMobileGuiQML_global.h"
#include "iplugin.h"

namespace Plugins
{
    class SAFRIMOBILEGUIQMLSHARED_EXPORT SafriMobileGuiQML: public PluginSystem::IPlugin{

        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "SafriMobileGuiQML" FILE "safrimobileguiqml.json")

    public:

        SafriMobileGuiQML();
        bool initialize(QStringList &arguments);


    };
}

#endif // SAFRIMOBILEGUIQML_H
