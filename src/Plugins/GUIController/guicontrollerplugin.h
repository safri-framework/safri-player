#ifndef GUICONTROLLERPLUGIN_H
#define GUICONTROLLERPLUGIN_H

#include "GUIController_global.h"
#include "iplugin.h"

namespace Plugins
{
    class GUICONTROLLERSHARED_EXPORT GUIControllerPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        public:

            GUIControllerPlugin();
            bool initialize(QStringList &arguments);
    };
}

#endif // GUICONTROLLERPLUGIN_H
