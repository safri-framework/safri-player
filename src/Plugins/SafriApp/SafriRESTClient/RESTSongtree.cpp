#include "RESTSongtree.h"

#include "RESTClient.h"
#include "RESTSongtreeItem.h"

using namespace SafriRESTClient;

RESTSongtree::RESTSongtree(QString restLocation, QObject *parent) :
    QObject(parent), client(0), rootItem(0)
{
    client = new RESTClient(restLocation, this);
    rootItem = new RESTSongtreeItem(client);
    rootItem->fetchChilds();
}

Core::ITreeItem *RESTSongtree::getRoot()
{
    return rootItem;
}
