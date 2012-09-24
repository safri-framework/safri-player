#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "PluginSystem_global.h"
#include "iplugin.h"

#include <QObject>
#include <QList>
#include <QStringList>

namespace PluginSystem
{
    class PluginSpec;

    class PLUGINSYSTEMSHARED_EXPORT PluginManager : public QObject
    {
        Q_OBJECT
        public:

            PluginManager(QStringList pluginPaths);

            /**
                \brief  Method the access the PluginManager instance.

                returns the unique PluginManager instance
            */
            static PluginManager *instance();

            /**
                \brief  Method for adding objects to the object pool.

                        Plugins could provide functionality to other plugins by adding
                        objects to the object pool.
            */
            void addObject(QObject *object);

            /**
                \brief  Method for removing objects from the object pool.

                        Plugins could provide functionality to other plugins by adding
                        objects to the object pool.
            */
            void removeObject(QObject *object);

            /**
                \brief  Returns all objects from the object pool
            */
            QList<QObject*>& getObjects();

            /**
                \brief  Retuns all objects with the given type from the object pool.
            */
            template <typename T> QList<T *> getObjects()
            {
                QList<QObject *> all = getObjects();
                QList<T *> result;
                foreach (QObject *obj, all)
                {
                    T* t = qobject_cast<T*>(obj);
                    if (t != 0)
                    {
                        result.append(t);
                    }
                }
                return result;
            }

            bool loadPlugins();

        signals:

            void objectAdded(QObject *object);
            void objectAboutToRemove(QObject *object);

        private:

            static PluginManager *m_instance;
            QList<QObject*> objectPool;
            QStringList pluginPaths;

            QList<PluginSpec*> plugins;
    };
}

#endif // PLUGINMANAGER_H
