#include "RESTSongtreeItem.h"

#include "RESTClient.h"
#include "RESTActions.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QRegExp>
#include <QDebug>
#include <QVariantMap>

#include <QEventLoop>

using namespace SafriRESTClient;

RESTSongtreeItem::RESTSongtreeItem(RESTClient *client, int itemID, int prefetchedChildCount, Core::BasicTreeItem *parentItem, QObject *parent) :
    Core::BasicTreeItem(parentItem, parent), client(client), childsFetched(false), prefetchedChildCount(prefetchedChildCount), itemID(itemID)
{
}

int RESTSongtreeItem::getChildCount()
{
    if (!childsFetched)
    {
        // fallback if childs not yet loaded
        return prefetchedChildCount;
    }
    else
    {
        // once the childs are loaded we can use the default implementation
        return BasicTreeItem::getChildCount();
    }
}

Core::ITreeItem *RESTSongtreeItem::getChildAt(int index)
{
    if (!childsFetched)
    {
        // currently loads the childs synchronously
        fetchChilds();
    }

    return BasicTreeItem::getChildAt(index);
}

void RESTSongtreeItem::fetchChilds()
{
    /*
    if (parentItem != 0)
    {
        qDebug() << "Fetch Childs of item ID: " << itemID << " - " << property("name");
    }
    */

    QString songtreeRequest = RESTAction::SONGTREE_GET_ITEM;
    songtreeRequest.replace(QRegExp("%%ITEMID%%"), QString::number(itemID));

    QNetworkReply *reply = client->sendRequest(songtreeRequest, this, SLOT(RESTReply()));

    // start an event loop to wait synchronously for the REST request to finish
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

void RESTSongtreeItem::RESTReply()
{
    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    if ( !reply )
    {
        qDebug() << "network reply null";
    }
    else
    {
        if(reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError)
        {
            QJsonDocument jsonDoc = QJsonDocument::fromJson( reply->readAll() );
            QJsonArray jsonItemArray = jsonDoc.array();
            QJsonObject jsonItem, jsonDataItem;
            QVariantMap itemMap, dataItemMap;
            RESTSongtreeItem* newTreeItem = 0;

            int itemCount = jsonItemArray.size();

            for (int i = 0; i < itemCount; i++)
            {
                jsonItem = jsonItemArray.at(i).toObject();
                jsonDataItem = jsonItem["dataItem"].toObject();

                itemMap = jsonItem.toVariantMap();
                dataItemMap = jsonDataItem.toVariantMap();

                newTreeItem = new RESTSongtreeItem(this->client, itemMap.value("treeItemId").toInt(),
                                                   itemMap.value("numberOfChilds").toInt(), this, this);

                //qDebug() << "new item with ID " << itemMap.value("treeItemId").toInt() << " - " <<
                //            dataItemMap.value("name").toString();

                newTreeItem->setProperty("name", dataItemMap.value("name").toString());
                newTreeItem->setProperty("itemID", itemMap.value("treeItemId").toInt());
                newTreeItem->setProperty("nodeType", itemMap.value("type").toString());

                addChild(newTreeItem);
            }

            childsFetched = true;
        }

        reply->deleteLater();
    }
}
