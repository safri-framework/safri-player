#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QReadWriteLock>
#include "CorePlugin_global.h"
#include "SettingsModule.h"

namespace Core
{
    class COREPLUGINSHARED_EXPORT SettingsManager : public QObject
    {
        Q_OBJECT
        public:

            bool                        registerModule(SettingsModule* module);
            bool                        removeModule(QString modulname);
            SettingsModule*             getModule(QString modulname);

            QStringList                 getRegisteredModules();

            bool                        loadSettings();
            bool                        saveSettings();

            static SettingsManager*     getInstance();

        private:

            // Singleton pattern
            explicit SettingsManager(QObject *parent = 0);

            QMap<QString, SettingsModule*> modules;

            QReadWriteLock lock;
    };
}

#endif // SETTINGSMANAGER_H
