#include "SafriAppPlugin.h"
#include <QDebug>
#include <QtWidgets/QWidget>
#include "SafriAppInstance.h"

#include "LocalAppController.h"
#include "SafriRESTClient/RESTAppController.h"

#include "SafriRESTClient/RESTSongtree.h"
#include "Interfaces/ITreeItem.h"

#include "icore.h"
#include "Settings/SettingsManager.h"

using namespace Plugins;
using namespace SafriRESTClient;

SafriAppPlugin::SafriAppPlugin()
{

}

bool SafriAppPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    bool isRESTClient;
    SafriAppInstance* instance;
    Q_UNUSED(instance)

    Core::SettingsModule *appSettings = Core::ICore::settingsManager()->getModule("org.safri.app");
    isRESTClient = appSettings->getSetting("isRESTClient").toBool();

    if (isRESTClient)
    {
        instance = new SafriAppInstance(new RESTAppController() );
    }
    else
    {
        instance = new SafriAppInstance(new LocalAppController() );
    }

    return true;
}

