#ifndef SAFRIMOBILEGUIQML_H
#define SAFRIMOBILEGUIQML_H

#include "SafriMobileGuiQML_global.h"
#include "iplugin.h"

namespace Plugins
{
    class SAFRIMOBILEGUIQMLSHARED_EXPORT SafriMobileGuiQML: public PluginSystem::IPlugin{

        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)

    public:

        SafriMobileGuiQML();
        bool initialize(QStringList &arguments);


    };
}

#endif // SAFRIMOBILEGUIQML_H
