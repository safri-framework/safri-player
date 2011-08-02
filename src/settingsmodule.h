#ifndef SETTINGSMODULE_H
#define SETTINGSMODULE_H

#include <QObject>
#include <QVariant>
#include <QString>
#include <QMap>

class SettingsModule : public QObject
{
    Q_OBJECT
    public:

        SettingsModule(QString moduleName);

        virtual QString getModulename();
        virtual QVariant getSetting(QString setting);
        virtual void setSetting(QString setting, QVariant value);

        virtual bool saveSettings();
        virtual bool loadSettings();

    signals:

        virtual void settingsChanged();

    protected:

        QMap<QString, QVariant> settings;
        bool modified;
        QString moduleName;
};

#endif // SETTINGSMODULE_H
