#include "SafriAppPlugin.h"
#include <QDebug>
#include <QtWidgets/QWidget>
#include "SafriAppInstance.h"
#include "SafriRESTClient/RESTPlaybackController.h"
#include "LocalAppController.h"
#include "SafriRESTClient/RESTAppController.h"

#include "SafriRESTClient/RESTSongtree.h"
#include "Interfaces/ITreeItem.h"

using namespace Plugins;
using namespace SafriRESTClient;

SafriAppPlugin::SafriAppPlugin()
{

}

bool SafriAppPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)

    RESTPlaybackController* playbackController = new RESTPlaybackController("http://192.168.1.87:8085/");
    //RESTSongtree* songTree = new RESTSongtree("http://192.168.1.87:8085/");

    /*
    Core::ITreeItem* root = songTree->getRoot();
    qDebug() << "root child count: " << root->getChildCount();

    root = root->getChildAt(1);
    qDebug() << "2nd child count: " << root->getChildCount() << " name: " << root->property("name");

    root = root->getChildAt(0);
    qDebug() << "3rd child count: " << root->getChildCount() << " name: " << root->property("name");;
    */

    addObject(playbackController);

    //SafriAppInstance* instance = new SafriAppInstance(new LocalAppController() );
    SafriAppInstance* instance = new SafriAppInstance(new RESTAppController() );
    Q_UNUSED(instance)

    return true;
}

