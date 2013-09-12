#include "SafriAppInstance.h"

#include "ViewController.h"

#include "LocalAppController.h"
#include "SafriRESTClient/RESTAppController.h"

#include "Interfaces/ICore.h"
#include "Settings/SettingsManager.h"

#include <QDebug>
#include <QTcpSocket>

using namespace SafriRESTClient;

SafriAppInstance::SafriAppInstance(QObject *parent) :
    QObject(parent)
{


    Core::SettingsModule *appSettings = Core::ICore::settingsManager()->getModule("org.safri.app");
    isRESTClient = appSettings->getSetting("isRESTClient").toBool();

    if (isRESTClient)
    {
        RESTAppController* restAppController  = new RESTAppController();
        connect(restAppController, SIGNAL( connectionFailed() ), this, SLOT(    connectionFailed()  ));
        appController = restAppController;

    }
    else
    {
        appController = new LocalAppController();
    }

    viewController = new ViewController(appController);
    connect(viewController, SIGNAL(requestConnect(QString,int)),    this, SLOT(connectTo(QString,int)));
    connect(viewController, SIGNAL(requestDisconnect()),            this, SLOT(disconnect()));
}


void SafriAppInstance::connectTo(QString host, int port)
{
    qDebug() << "SafriAppInstance::connectTo - host: " << host << " / port: " << port;

    QTcpSocket testSocket;

    testSocket.connectToHost(host, port);

    // first we test, if the host is reachable
    if ( testSocket.waitForConnected(5000) )
    {
        testSocket.close();
        isRESTClient = true;
        Core::SettingsModule *restSettings = Core::ICore::settingsManager()->getModule("org.safri.restapi");
        Core::SettingsModule *appSettings = Core::ICore::settingsManager()->getModule("org.safri.app");
        restSettings->setSetting("host", host);
        restSettings->setSetting("port", port);
        appSettings->setSetting("isRESTClient", true);
        Core::ICore::settingsManager()->saveSettings();

        delete appController;

        RESTAppController* restAppController  = new RESTAppController();
        connect(restAppController, SIGNAL( connectionFailed() ), this, SLOT(    connectionFailed()  ));
        appController = restAppController;
        viewController->changeAppController(appController);
    }
    else
    {
        viewController->showErrorMessage("Sorry, can't connect to Safri.");
    }
}

void SafriAppInstance::disconnect()
{
    qDebug() << "SafriAppInstance::disconnect()";
    Core::SettingsModule *appSettings = Core::ICore::settingsManager()->getModule("org.safri.app");
    IAppController* oldAppController;

    if (isRESTClient)
    {
        oldAppController = appController;

        oldAppController->shutdown();

        appController = new LocalAppController();
        viewController->changeAppController(appController);
        appSettings->setSetting("isRESTClient", false);

        Core::ICore::settingsManager()->saveSettings();

        isRESTClient = false;

        // as everything needed for the disconnect was done
        // in the app controllers shutdown method, we delay
        // the destruction of the old app controller a little bit
        // that should give all remaining signals&slots the chance to handle the
        // change without ending up with an already deleted object
        oldAppController->deleteLater();
    }
}

void SafriAppInstance::connectionFailed()
{
    qDebug()<<"FAILED";
    viewController->showErrorMessage("Sorry, can't connect to Safri.");
    disconnect();
}
