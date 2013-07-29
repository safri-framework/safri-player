#include "RESTSongtree.h"

#include "RESTClient.h"
#include "RESTSongtreeItem.h"
#include <QDebug>

using namespace SafriRESTClient;

RESTSongtree::RESTSongtree(RESTClient* restClient, QObject *parent) :
    QObject(parent), client(restClient), rootItem(0)
{
    rootItem = new RESTSongtreeItem(client, this);
    rootItem->fetchChilds();
}

RESTSongtree::~RESTSongtree()
{
    qDebug() << "DESTRUCT RESTSongtree";
}

Core::ITreeItem *RESTSongtree::getRoot()
{
    return rootItem;
}
