#include "settingsmanager.h"
#include "settingsmodule.h"

SettingsManager::SettingsManager(QObject *parent) : QObject(parent)
{
    SettingsModule* coreViewSM = new SettingsModule("core.view");
    SettingsModule* albumSM = new SettingsModule("core.albumCover");

    this->registerModule(coreViewSM);
    this->registerModule(albumSM);

    this->loadSettings();
}

bool SettingsManager::registerModule(SettingsModule* module)
{
    modules.insert(module->getModulename(), module);
}

bool SettingsManager::removeModule(QString modulename)
{
    modules.remove(modulename);
}

SettingsModule* SettingsManager::getModule(QString modulename)
{
    return modules.value(modulename, 0);
}

QStringList SettingsManager::getRegisteredModules()
{
    QStringList moduleCaptions;

    QMapIterator<QString, SettingsModule*> i(modules);

    while ( i.hasNext() )
    {
        i.next();
        moduleCaptions.append( i.key() );
    }

    return moduleCaptions;
}

bool SettingsManager::loadSettings()
{
    QMapIterator<QString, SettingsModule*> i(modules);

    while ( i.hasNext() )
    {
        i.next();
        SettingsModule* modul = i.value();

        modul->loadSettings();
    }
}

bool SettingsManager::saveSettings()
{
    QMapIterator<QString, SettingsModule*> i(modules);

    while ( i.hasNext() )
    {
        i.next();
        SettingsModule* modul = i.value();

        modul->saveSettings();
    }
}

// Singleton pattern
SettingsManager* SettingsManager::getInstance()
{
    static SettingsManager theInstance;

    return &theInstance;
}
