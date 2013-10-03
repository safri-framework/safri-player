#include "SettingsModule.h"

using namespace Core;

SettingsModule::SettingsModule(QString moduleName, QObject *parent) :
    ISettingsModule(parent), moduleName(moduleName), lock(QReadWriteLock::Recursive)
{
}

QString SettingsModule::getModulename()
{
    return moduleName;
}

QVariant SettingsModule::getSetting(QString setting)
{
    QVariant settingResult;

    lock.lockForRead();
        settingResult = settings.value(setting, QVariant() );
    lock.unlock();

    return settingResult;
}

void SettingsModule::setSetting(QString setting, QVariant value)
{
    if ( getSetting(setting) != value )
    {
        lock.lockForWrite();
            //qDebug() << "Setting modified: " << moduleName + "." + setting << " -> " << value.toString() ;
            modified = true;
            settings.insert(setting, value);
        lock.unlock();

        Q_EMIT settingsChanged(setting);
    }
}

QMap<QString, QVariant> SettingsModule::getSettingsMap()
{
    QMap<QString, QVariant> map;

    lock.lockForRead();
        map = settings;
    lock.unlock();

    return map;
}

void SettingsModule::setSettingsMap(QMap<QString, QVariant> settings)
{
    lock.lockForWrite();
        this->settings = settings;
    lock.unlock();
}

bool SettingsModule::isModified()
{
    bool resultModified = false;

    lock.lockForWrite();
        if (modified)
        {
            // reset by read:
            // soon as the user noticed the modification, we reset the flag
            modified = false;

            resultModified = true;
        }
    lock.unlock();

    return resultModified;
}
