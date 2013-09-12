#include "SettingsManager.h"

#include <QDomComment>
#include <QDomElement>
#include <QFile>
#include <QDomNodeList>
#include <QTextStream>
#include <QDebug>

#include "Interfaces/ICore.h"

using namespace Core;

SettingsManager::SettingsManager(QObject *parent) :
    QObject(parent)
{
    this->registerModule( new SettingsModule("org.safri.core.view") );
    this->registerModule( new SettingsModule("org.safri.collection") );
    this->registerModule( new SettingsModule("org.safri.core.albumCover") );

    this->loadSettings();
}


bool SettingsManager::registerModule(SettingsModule *module)
{
    modules.insert(module->getModulename(), module);

    return true;
}

bool SettingsManager::removeModule(QString modulname)
{
    modules.remove(modulname);

    return true;
}

SettingsModule *SettingsManager::getModule(QString modulname)
{
    return modules.value(modulname, 0);
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
    QDomDocument domDoc("settingsdom");

    QFile file(ICore::storageDirectory() + "/safri-config.xml");
    if (!file.open(QIODevice::ReadOnly))
         return false;

     if (!domDoc.setContent(&file))
     {
         file.close();

         return false;
     }
     file.close();

     QDomElement docElem = domDoc.documentElement();

     QDomNodeList settingsModules = docElem.elementsByTagName("settingsmodule");

     qDebug() << "LOAD SETTINGS!";

     int modulesCount = settingsModules.size();
     for (int m = 0; m < modulesCount; m++)
     {
         QDomElement module = settingsModules.at(m).toElement();

         QString moduleName = module.attribute("name");

         SettingsModule* sModule = modules.value(moduleName, 0);

         if (sModule == 0)
         {
             sModule = new SettingsModule(moduleName);
             this->registerModule(sModule);
         }

         QDomNodeList settings = module.elementsByTagName("setting");

         QMap<QString, QVariant> settingsMap;


         int settingsCount = settings.size();

         for (int s = 0; s < settingsCount; s++)
         {
             QDomElement setting = settings.at(s).toElement();

             //qDebug() << setting.attribute("name") << ":" << setting.text();
             settingsMap.insert(setting.attribute("name"), setting.text());
         }

         sModule->setSettingsMap(settingsMap);
     }

     return true;
}

bool SettingsManager::saveSettings()
{
    QDomDocument domDoc;

    QDomElement root = domDoc.createElement("safri-configuration");
    domDoc.appendChild(root);

    QMapIterator<QString, SettingsModule*> i(modules);

    while ( i.hasNext() )
    {
        i.next();
        SettingsModule* settingsModule = i.value();

        QDomElement module = domDoc.createElement("settingsmodule");
        module.setAttribute("name", settingsModule->getModulename());

        QMap<QString, QVariant> settingsMap = settingsModule->getSettingsMap();

        QMapIterator<QString, QVariant> s(settingsMap);

        while ( s.hasNext() )
        {
            s.next();
            QDomElement settingsElement = domDoc.createElement("setting");
            settingsElement.setAttribute("name", s.key());
            QDomText text = domDoc.createTextNode(s.value().toString());
            settingsElement.appendChild(text);

            module.appendChild(settingsElement);
        }

        root.appendChild(module);

    }

    QFile file(ICore::storageDirectory() + "/safri-config.xml");

    if( !file.open( QIODevice::ReadWrite ) )
    {
        qDebug() << "FILE NOT OPEN " << file.errorString();
        return false;
    }

    QTextStream ts( &file );
    ts << domDoc.toString(4);

    file.close();

    return true;
}

SettingsManager *SettingsManager::getInstance()
{
    static SettingsManager theInstance;

    return &theInstance;
}
