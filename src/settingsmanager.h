#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QMap>
#include <QStringList>

class SettingsModule;

class SettingsManager : public QObject
{
    Q_OBJECT
    public:

        bool registerModule(SettingsModule*);
        bool removeModule(QString modulname);
        SettingsModule* getModule(QString modulname);

        QStringList getRegisteredModules();

        bool loadSettings();
        bool saveSettings();

        static SettingsManager* getInstance();

    private:

        // Singleton pattern
        explicit SettingsManager(QObject *parent = 0);

        QMap<QString, SettingsModule*> modules;

};

#endif // SETTINGSMANAGER_H
