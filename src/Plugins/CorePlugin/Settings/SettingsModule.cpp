#include "SettingsModule.h"

using namespace Core;

SettingsModule::SettingsModule(QString moduleName, QObject *parent) :
    ISettingsModule(parent), moduleName(moduleName)
{
}

QString SettingsModule::getModulename()
{
    return moduleName;
}

QVariant SettingsModule::getSetting(QString setting)
{
    return settings.value(setting, QVariant() );
}

void SettingsModule::setSetting(QString setting, QVariant value)
{
    if (settings.value(setting, QVariant()) != value )
    {
        //qDebug() << "Setting modified: " << moduleName + "." + setting << " -> " << value.toString() ;
        modified = true;
        settings.insert(setting, value);

        Q_EMIT settingsChanged(setting);
    }
}

QMap<QString, QVariant> SettingsModule::getSettingsMap()
{
    return settings;
}

void SettingsModule::setSettingsMap(QMap<QString, QVariant> settings)
{
    this->settings = settings;
}

bool SettingsModule::isModified()
{
    if (modified)
    {
        // reset by read:
        // soon as the user noticed the modification, we reset the flag
        modified = false;

        return true;
    }

    return false;
}
