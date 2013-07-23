#include "RESTSongtree.h"

#include "RESTClient.h"
#include "RESTSongtreeItem.h"

using namespace SafriRESTClient;

RESTSongtree::RESTSongtree(RESTClient* restClient, QObject *parent) :
    QObject(parent), client(restClient), rootItem(0)
{
    rootItem = new RESTSongtreeItem(client);
    rootItem->fetchChilds();
}

Core::ITreeItem *RESTSongtree::getRoot()
{
    return rootItem;
}
