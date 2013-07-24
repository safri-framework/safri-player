#include "RESTAppController.h"
#include "SafriRESTClient/RESTPlaybackController.h"
#include "SafriRESTClient/RESTSongtree.h"
#include "SafriRESTClient/RESTSongtreeModel.h"
#include "RESTPlaylist.h"
#include "RESTPlaylistModel.h"
#include "RESTClient.h"
#include "icore.h"
#include "Settings/SettingsManager.h"
#include "Interfaces/ITreeItem.h"
#include "RESTActions.h"

#include <QDebug>
#include <QRegExp>
#include <QNetworkReply>
#include <QEventLoop>

#include "pluginmanager.h"

using namespace SafriRESTClient;

RESTAppController::RESTAppController(QObject *parent) :
    IAppController(parent), playlist(0), playlistModel(0)
{
    restClient = new RESTClient( getRESTLocation() );

    playbackController = new RESTPlaybackController(restClient);
    PluginSystem::PluginManager::instance()->addObject( playbackController );

}

QAbstractItemModel *RESTAppController::getSongtreeModel()
{
    songtree = new RESTSongtree(restClient);
    songtreeModel = new RESTSongtreeModel(songtree->getRoot(), this);

    return songtreeModel;
}

QAbstractItemModel *RESTAppController::getPlaylistModel()
{
    if(playlistModel)
        delete playlistModel;

    if(playlist)
        delete playlist;

    playlist = new RESTPlaylist(restClient, this);
    playlistModel = new RESTPlaylistModel(playlist, this);
    connect(playlist, SIGNAL(resetModel()), this, SLOT(resetPlaylistModel()));

    return playlistModel;
}

void RESTAppController::moveMediaInPlaylist(int from, int to)
{
    playlist->moveMedia(from, to);
}

void RESTAppController::playTreeModelIndex(QModelIndex treeIndex)
{
    playbackController->stopAction()->trigger();

    Core::ITreeItem* treeItem = static_cast<Core::ITreeItem*>(treeIndex.internalPointer());
    int itemId = treeItem->property("itemID").toInt();

    insertSongtreeNodeInPlaylist(itemId, -1);

    if (playbackController->playAction()->isEnabled())
    {
        qDebug() << "playAction enabled";
        playbackController->playAction()->trigger();
    }
    qDebug()<<Q_FUNC_INFO<<"    HALLO???";

}

void RESTAppController::enqueueTreeModelIndex(QModelIndex treeIndex)
{
    // Q_UNUSED treeIndex;
}

void RESTAppController::playPlaylistIndex(int index)
{
    playlist->playPlaylistIndex(index);
}

void RESTAppController::removeIndexFromPlaylist(int index)
{
    qDebug()<<"DELETE";
    playlist->removeIndexFromPlaylist(index);
}

QString RESTAppController::getRESTLocation()
{
    Core::SettingsModule *restSettings = Core::ICore::settingsManager()->getModule("org.safri.restapi");
    QString restLocation = "http://" + restSettings->getSetting("host").toString() + ":" + restSettings->getSetting("port").toString() + "/";

    //qDebug() << "Rest Location from Settings: " << restLocation;

    return restLocation;
}

void RESTAppController::insertSongtreeNodeInPlaylist(int itemID, int position)
{
    QString request = RESTAction::SONGTREE_INSERT_ITEM;

    request.replace(QRegExp("%%ITEMID%%"), QString::number(itemID));
    request.replace(QRegExp("%%PLAYLISTPOS%%"), QString::number(position));
    qDebug()<<Q_FUNC_INFO<<"  "<<request;
    QNetworkReply *reply = restClient->sendRequest(request);

    // start an event loop to wait synchronously for the REST request to finish
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    reply = restClient->sendRequest(RESTAction::PLAYLIST_SET_AS_CURRENT);

    // start an event loop to wait synchronously for the REST request to finish
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

void RESTAppController::resetPlaylistModel()
{
    //TMP Q_EMIT newPlaylistModel();
}
