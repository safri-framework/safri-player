#include "settingsmodule.h"
#include "databasedao.h"

#include <QDebug>

SettingsModule::SettingsModule(QString moduleName) : moduleName(moduleName)
{

}

QVariant SettingsModule::getSetting(QString setting)
{
    //qDebug() << "No. of settings: " << settings.size() << moduleName + "." + setting;
    return this->settings.value(moduleName + "." + setting, QVariant() );
}

void SettingsModule::setSetting(QString setting, QVariant value)
{
    if (this->settings.value(moduleName + "." + setting, QVariant()) != value )
    {
        //qDebug() << "Setting modified: " << moduleName + "." + setting << " -> " << value.toString() ;
        this->modified = true;
        this->settings.insert(moduleName + "." + setting, value);

        //Q_EMIT settingsChanged();
    }
}

QString SettingsModule::getModulename()
{
    return this->moduleName;
}

bool SettingsModule::saveSettings()
{
    if (this->modified)
    {
        DatabaseDAO::removeModuleSettings(moduleName);
        DatabaseDAO::insertModuleSettings(settings);
        this->modified = false;
        //qDebug() << "saved " << settings.size() << " settings into database";
    }
}

bool SettingsModule::loadSettings()
{
    this->settings = DatabaseDAO::getModuleSettings(moduleName);
    this->modified = false;

    Q_EMIT settingsChanged();

    //qDebug() << "loaded " << settings.size() << " settings from database";
}
