#include "RESTAppController.h"
#include "SafriRESTClient/RESTPlaybackController.h"
#include "SafriRESTClient/RESTSongtree.h"
#include "SafriRESTClient/RESTSongtreeModel.h"
#include "icore.h"
#include "Settings/SettingsManager.h"

#include <QDebug>

#include "pluginmanager.h"

using namespace SafriRESTClient;

RESTAppController::RESTAppController(QObject *parent) :
    IAppController(parent)
{
    RESTPlaybackController* playbackController = new RESTPlaybackController(getRESTLocation());
    PluginSystem::PluginManager::instance()->addObject( playbackController  );
}

QAbstractItemModel *RESTAppController::getSongtreeModel()
{
    songtree = new RESTSongtree(getRESTLocation());
    songtreeModel = new RESTSongtreeModel(songtree->getRoot(), this);

    return songtreeModel;
}

QString RESTAppController::getRESTLocation()
{
    Core::SettingsModule *restSettings = Core::ICore::settingsManager()->getModule("org.safri.restapi");
    QString restLocation = "http://" + restSettings->getSetting("host").toString() + ":" + restSettings->getSetting("port").toString() + "/";

    qDebug() << "Rest Location from Settings: " << restLocation;

    return restLocation;

    //return "http://192.168.1.87:8085/";
}
