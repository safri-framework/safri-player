#ifndef SETTINGSMODULE_H
#define SETTINGSMODULE_H

#include <QObject>
#include <QVariant>
#include <QString>
#include <QMap>

class SettingsModule : public QObject
{
    Q_OBJECT

    friend class SettingsManager;
    friend class SettingsModuleWidget;

    public:

        SettingsModule(QString moduleName);

        virtual QString getModulename();
        virtual QVariant getSetting(QString setting);
        virtual void setSetting(QString setting, QVariant value);

    signals:

        void settingsChanged(QString setting);

    protected:

        QMap<QString, QVariant>* getSettingsMap();
        void setSettingsMap(QMap<QString, QVariant>* settings);
        bool isModified();

        QMap<QString, QVariant>* settings;
        bool modified;
        QString moduleName;
};

#endif // SETTINGSMODULE_H
