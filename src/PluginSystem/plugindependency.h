#ifndef PLUGINDEPENDENCY_H
#define PLUGINDEPENDENCY_H

#include "PluginSystem_global.h"

#include <QObject>

namespace PluginSystem
{

    class PLUGINSYSTEMSHARED_EXPORT PluginDependency : public QObject
    {
        Q_OBJECT

        public:

            explicit PluginDependency(QString name, QString version, QObject *parent = 0);
            bool operator<=(PluginDependency& rhs);
            bool operator==(PluginDependency& rhs);
            QString getVersion();
            QString getName();

        private:

            QString name;
            QString version;

    };
}

#endif // PLUGINDEPENDENCY_H
