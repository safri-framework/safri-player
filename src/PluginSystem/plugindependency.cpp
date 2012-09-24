#include "plugindependency.h"

using namespace PluginSystem;

PluginDependency::PluginDependency(QString name, QString version, QObject *parent) :
    QObject(parent), name(name), version(version)
{

}

bool PluginDependency::operator<=(PluginDependency& rhs)
{
    if(name == rhs.getName())
    {
        if(this->version.remove('.').toInt() <= rhs.getVersion().remove('.').toInt())
            return true;
    }
    return false;
}

bool PluginDependency::operator ==(PluginDependency& rhs)
{
    return (this->version == rhs.getVersion() && this->name == rhs.getName());

}

QString PluginDependency::getVersion()
{
    return version;
}

QString PluginDependency::getName()
{
    return name;
}
