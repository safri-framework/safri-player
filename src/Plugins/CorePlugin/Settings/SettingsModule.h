#ifndef SETTINGSMODULE_H
#define SETTINGSMODULE_H

#include "Interfaces/ISettingsModule.h"
#include <QMap>

namespace Core
{
    class COREPLUGINSHARED_EXPORT SettingsModule : public ISettingsModule
    {
        friend class SettingsManager;
        friend class SettingsModuleWidget;

        Q_OBJECT
        public:

            explicit SettingsModule(QString moduleName, QObject *parent = 0);

            virtual QString             getModulename();
            virtual QVariant            getSetting(QString setting);
            virtual void                setSetting(QString setting, QVariant value);
            bool                        isModified();


        protected:

            QMap<QString, QVariant>     getSettingsMap();
            void                        setSettingsMap(QMap<QString, QVariant> settings);


            QMap<QString, QVariant> settings;
            bool modified;
            QString moduleName;


    };
}

#endif // SETTINGSMODULE_H
