#include "SafriAppInstance.h"

#include "ViewController.h"

#include "LocalAppController.h"
#include "SafriRESTClient/RESTAppController.h"

#include "icore.h"
#include "Settings/SettingsManager.h"

#include <QDebug>

using namespace SafriRESTClient;

SafriAppInstance::SafriAppInstance(QObject *parent) :
    QObject(parent)
{


    Core::SettingsModule *appSettings = Core::ICore::settingsManager()->getModule("org.safri.app");
    isRESTClient = appSettings->getSetting("isRESTClient").toBool();

    if (isRESTClient)
    {
        appController = new RESTAppController();

    }
    else
    {
        appController = new LocalAppController();
    }

    viewController = new ViewController(appController);
    connect(viewController, SIGNAL(requestConnect(QString,int)), this, SLOT(connectTo(QString,int)));
    connect(viewController, SIGNAL(requestDisconnect()), this, SLOT(disconnect()));
}


void SafriAppInstance::connectTo(QString host, int port)
{
    qDebug() << "SafriAppInstance::connectTo - host: " << host << " / port: " << port;


    Core::SettingsModule *restSettings = Core::ICore::settingsManager()->getModule("org.safri.restapi");
    Core::SettingsModule *appSettings = Core::ICore::settingsManager()->getModule("org.safri.app");

    restSettings->setSetting("host", host);
    restSettings->setSetting("port", port);
    appSettings->setSetting("isRESTClient", true);

    Core::ICore::settingsManager()->saveSettings();

    delete appController;

    appController = new RESTAppController();
    viewController->changeAppController(appController);

    isRESTClient = true;
}

void SafriAppInstance::disconnect()
{
    qDebug() << "SafriAppInstance::disconnect()";
    Core::SettingsModule *appSettings = Core::ICore::settingsManager()->getModule("org.safri.app");

    if (isRESTClient)
    {
        delete appController;

        appController = new LocalAppController();
        viewController->changeAppController(appController);
        appSettings->setSetting("isRESTClient", false);

        Core::ICore::settingsManager()->saveSettings();

        isRESTClient = false;
    }
}
