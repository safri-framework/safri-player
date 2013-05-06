#ifndef ISETTINGSMODULE_H
#define ISETTINGSMODULE_H

#include "CorePlugin_global.h"
#include <QObject>
#include <QVariant>
#include <QString>

namespace Core
{
    class COREPLUGINSHARED_EXPORT ISettingsModule : public QObject
    {
        Q_OBJECT
        public:
            explicit ISettingsModule(QObject *parent = 0);

            virtual QString     getModulename() = 0;
            virtual QVariant    getSetting(QString setting) = 0;
            virtual void        setSetting(QString setting, QVariant value) = 0;

        signals:

            void settingsChanged(QString setting);
    };
}

#endif // ISETTINGSMODULE_H
