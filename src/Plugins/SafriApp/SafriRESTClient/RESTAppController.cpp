#include "RESTAppController.h"
#include "SafriRESTClient/RESTPlaybackController.h"
#include "SafriRESTClient/RESTSongtree.h"
#include "SafriRESTClient/RESTSongtreeModel.h"
#include "RESTPlaylist.h"
#include "RESTPlaylistModel.h"
#include "RESTClient.h"
#include "Interfaces/ICore.h"
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
    IAppController(parent), songtree(0), songtreeModel(0), playlist(0), playlistModel(0)
{
    // first we store a pointer to the original playback controller
    localPlaybackController = Core::ICore::playbackController();

    localPlaybackController->stopAction()->trigger();

    // we reset the playback controller with a new playlist
    // in the future we could maybe, leave the controller as is
    // and use it's state as before the REST connect
    localPlaybackController->setPlaylist( Core::ICore::createPlaylist() );

    restClient = new RESTClient( getRESTLocation(), this );

    restPlaybackController = new RESTPlaybackController(restClient, this);

    connect (restPlaybackController, SIGNAL( connectionFailed() ), this, SIGNAL( connectionFailed() ) );

    PluginSystem::PluginManager::instance()->addObject( restPlaybackController  );
}

RESTAppController::~RESTAppController()
{
    qDebug() << "DESTRUCT RESTAppController";

    if (songtree)
    {
        delete songtree;
    }

    if (songtreeModel)
    {
        delete songtreeModel;
    }
}

QAbstractItemModel *RESTAppController::getSongtreeModel(TREE_HIERARCHY hierarchy)
{
    Q_UNUSED( hierarchy )
    songtree = new RESTSongtree(restClient);
    songtreeModel = new RESTSongtreeModel(songtree->getRoot());

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

QAbstractItemModel *RESTAppController::getCoverModel()
{
    return 0;
}

void RESTAppController::moveMediaInPlaylist(int from, int to)
{
    playlist->moveMedia(from, to);
}

void RESTAppController::playTreeModelIndex(QModelIndex treeIndex)
{
    restPlaybackController->stopAction()->trigger();

    Core::ITreeItem* treeItem = static_cast<Core::ITreeItem*>(treeIndex.internalPointer());
    int itemId = treeItem->property("itemID").toInt();

    insertSongtreeNodeInPlaylist(itemId, -1);

    if (restPlaybackController->playAction()->isEnabled())
    {
        qDebug() << "playAction enabled";
        restPlaybackController->playAction()->trigger();
    }
}

void RESTAppController::enqueueTreeModelIndex(QModelIndex treeIndex)
{
    Core::ITreeItem* treeItem = static_cast<Core::ITreeItem*>(treeIndex.internalPointer());

    int itemId = treeItem->property("itemID").toInt();

    insertSongtreeNodeInPlaylist(itemId, playlist->getSize());
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

void RESTAppController::setShuffle(bool enabled)
{
    playlist->setShuffle(enabled);
}

IAppController::APP_MODE RESTAppController::getMode()
{
    return IAppController::REST;
}

void RESTAppController::shutdown()
{
    // we remove the REST playback controller from the object pool and replace it
    // by the original (local) playback controller
    PluginSystem::PluginManager::instance()->removeObject( restPlaybackController );

    PluginSystem::PluginManager::instance()->addObject( localPlaybackController  );
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

    QNetworkReply* reply = restClient->sendRequest(request);

    // start an event loop to wait synchronously for the REST request to finish
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    reply->deleteLater();

    reply = restClient->sendRequest(RESTAction::PLAYLIST_SET_AS_CURRENT);

    // start an event loop to wait synchronously for the REST request to finish
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    reply->deleteLater();
}

void RESTAppController::resetPlaylistModel()
{
    //TMP Q_EMIT newPlaylistModel();
}
