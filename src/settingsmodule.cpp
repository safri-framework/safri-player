#include "settingsmodule.h"
#include "databasedao.h"

#include <QDebug>

SettingsModule::SettingsModule(QString moduleName)
    : settings(new QMap<QString, QVariant>()), modified(false), moduleName(moduleName)
{

}

QVariant SettingsModule::getSetting(QString setting)
{
    //qDebug() << "No. of settings: " << settings.size() << moduleName + "." + setting;
    return this->settings->value(setting, QVariant() );
}

void SettingsModule::setSetting(QString setting, QVariant value)
{
    if (this->settings->value(setting, QVariant()) != value )
    {
        //qDebug() << "Setting modified: " << moduleName + "." + setting << " -> " << value.toString() ;
        this->modified = true;
        this->settings->insert(setting, value);
    }
}

QString SettingsModule::getModulename()
{
    return this->moduleName;
}

QMap<QString, QVariant>* SettingsModule::getSettingsMap()
{
    return settings;
}

void SettingsModule::setSettingsMap(QMap<QString, QVariant>* settings)
{
    delete this->settings;
    this->settings = settings;
}

bool SettingsModule::isModified()
{

    if (modified)
    {

        Q_EMIT settingsChanged();

        // reset by read:
        // soon as the user noticed the modification, we reset the flag
        modified = false;

        return true;
    }

    return false;
}
