#include "RESTAppController.h"
#include "SafriRESTClient/RESTSongtree.h"
#include "RESTSongtreeModel.h"

using namespace SafriRESTClient;

RESTAppController::RESTAppController(QObject *parent) :
    IAppController(parent)
{
}

QAbstractItemModel *RESTAppController::getSongtreeModel()
{
    RESTSongtree* songTree = new RESTSongtree("http://192.168.1.87:8085/");
    return new RESTSongtreeModel(songTree->getRoot(), this);
}
