#include "pluginspec.h"
#include "iplugin.h"
#include "plugindependency.h"

#include <QFile>
#include <QFileInfo>
#include <QDomDocument>
#include <QDomNodeList>
#include <QPluginLoader>

#include <QDebug>

using namespace PluginSystem;

PluginSpec::PluginSpec(QString xmlPath) : plugin(0)
{
    QFileInfo fileInfo(xmlPath);

    location = fileInfo.absolutePath();

    readXML(xmlPath);
}

QString PluginSpec::getName()
{
    return name;
}

QString PluginSpec::getVersion()
{
    return version;
}

QString PluginSpec::getVendor()
{
    return vendor;
}

QString PluginSpec::getCopyright()
{
    return copyright;
}

QString PluginSpec::getLicense()
{
    return license;
}

QString PluginSpec::getDescription()
{
    return description;
}

QString PluginSpec::getUrl()
{
    return url;
}

QString PluginSpec::getCategory()
{
    return category;
}

IPlugin *PluginSpec::getPlugin()
{
    return plugin;
}

void PluginSpec::loadLibrary()
{

    #ifdef Q_OS_WIN
        QString libName = QString("%1/%2.dll").arg(location).arg(name);
    #elif defined(Q_OS_MAC)
        QString libName = QString("%1/lib%2.dylib").arg(location).arg(name);
    #elif defined(ANDROID)
        QString libName = QString("%1/lib%2.so").arg(ANDROID_LIB_PATH).arg(name);
    #else
        QString libName = QString("%1/lib%2.so").arg(location).arg(name);
    #endif

    qDebug() << "\nLoading library: " << libName;

    QPluginLoader loader(libName);

    if (!loader.load())
    {
        qDebug() << "Can't load plugin: " << name << ":" << loader.errorString();
    }

    QObject *pluginObject = loader.instance();

    if (!pluginObject)
    {
        qDebug() << "loader.instance == 0!";
    }

    plugin = qobject_cast<PluginSystem::IPlugin*>(pluginObject);
    if (plugin == 0)
    {
        qDebug() << "Can't upcast pluginObject to IPlugin interface";
    }
}

void PluginSpec::readXML(QString path)
{
    QFile file;
    file.setFileName(path);

    if(file.open(QFile::ReadOnly))
    {
        QString xml = QLatin1String(file.readAll());
        QDomDocument doc;
        doc.setContent( xml );
        QDomNodeList domNodeList = doc.elementsByTagName( "SafriPlugin" );

        if ( domNodeList.isEmpty() )
        {
            return;
        }
        else
        {
            name        = domNodeList.at( 0 ).toElement().attribute("name");
            version     = domNodeList.at( 0 ).toElement().attribute( "version" );

            domNodeList = doc.elementsByTagName("vendor");
            vendor = domNodeList.at(0).toElement().text();

            domNodeList = doc.elementsByTagName("copyright");
            copyright = domNodeList.at(0).toElement().text();

            domNodeList = doc.elementsByTagName("license");
            license = domNodeList.at(0).toElement().text();

            domNodeList = doc.elementsByTagName("description");
            description = domNodeList.at(0).toElement().text();

            domNodeList = doc.elementsByTagName("url");
            url = domNodeList.at(0).toElement().text();

            domNodeList = doc.elementsByTagName("category");
            category = domNodeList.at(0).toElement().text();

            domNodeList = doc.elementsByTagName("dependency");

            for(int i = 0; i<domNodeList.count(); i++)
            {
                QString depName = domNodeList.at(i).toElement().attribute("name");
                QString depVersion = domNodeList.at(i).toElement().attribute("version");
                dependencies.append(new PluginDependency(depName, depVersion));
            }
        }
    }
    else
    {
        qDebug() << file.errorString();
    }
}
