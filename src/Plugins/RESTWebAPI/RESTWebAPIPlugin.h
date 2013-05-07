#ifndef RESTWEBAPIPLUGIN_H
#define RESTWEBAPIPLUGIN_H

#include "iplugin.h"
#include "RESTWebAPI_global.h"

class HttpListener;

namespace Plugins
{
    class RESTWEBAPISHARED_EXPORT RESTWebAPIPlugin : public PluginSystem::IPlugin
    {
        Q_OBJECT
        Q_INTERFACES(PluginSystem::IPlugin)
        Q_PLUGIN_METADATA(IID "RESTWebAPIPlugin" FILE "RESTWebAPI.json")

        public:

            RESTWebAPIPlugin();

            bool initialize(QStringList &arguments);

        private:

            HttpListener* listener;
    };
}

#endif // RESTWEBAPIPLUGIN_H
