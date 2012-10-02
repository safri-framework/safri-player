#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "PluginSystem_global.h"

#include <QtPlugin>
#include <QObject>
#include <QStringList>

namespace PluginSystem
{
    /**
        \brief  The IPlugin class is an abstract class that each
                plugin must implement.
    */
    class PLUGINSYSTEMSHARED_EXPORT IPlugin : public QObject
    {
        Q_OBJECT
        public:

            virtual ~IPlugin() {}

            /**
                \brief  Called after the plugin was loaded and the IPlugin instance
                        has been created.

                        Plugins should initialize their internal state in this function and returns
                        if the initilization was successfull. If it wasn't successful errorStr should
                        be set to a user-readable error description.

                \param  arguments to control the plugin, as specified in the specification file
                \returns success of initialisation
            */
            virtual bool initialize(QStringList &arguments) = 0;

            /**
                \brief  Called when the plugin will be unloaded.

                        Implement this method to clean up internal data of the plugin before it
                        will be unloaded. If the shutdown was finished emit the shutdownFinished signal.
                        This could also be used for a delayed shutdown.

                \returns true on success of shutdown or false for a delayed shutdown
            */
            virtual bool shutdown();

            /**
                \brief      Returns a user-readable message of the last error.

                \returns    user-readable error string
            */
            virtual QString errorString();

            /**
                \brief  Convenience method to register an object in the plugin manager's
                        object pool.
            */
            void addObject(QObject *object);

            /**
                \brief  Convenience method to unregister an object in the plugin manager's
                        object pool.
            */
            void removeObject(QObject *object);

        signals:

            void shutdownFinished();

        protected:

            QString errorStr;
    };
}

Q_DECLARE_INTERFACE(PluginSystem::IPlugin, "PluginSystem::IPlugin")

#endif // IPLUGIN_H
