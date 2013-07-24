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
    bool isRESTClient;
    ViewController* viewController;

    Core::SettingsModule *appSettings = Core::ICore::settingsManager()->getModule("org.safri.app");
    isRESTClient = appSettings->getSetting("isRESTClient").toBool();

    if (isRESTClient)
    {
        viewController = new ViewController(new RESTAppController() );
    }
    else
    {
        viewController = new ViewController(new LocalAppController() );
    }

    connect(viewController, SIGNAL(requestConnect(QString,int)), this, SLOT(connectTo(QString,int)));
    connect(viewController, SIGNAL(requestDisconnect()), this, SLOT(disconnect()));
}


void SafriAppInstance::connectTo(QString host, int port)
{
    qDebug() << "SafriAppInstance::connectTo - host: " << host << " / port: " << port;
}

void SafriAppInstance::disconnect()
{
    qDebug() << "SafriAppInstance::disconnect()";
}
