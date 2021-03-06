#include "PlaylistHelper.h"
#include "Interfaces/IPlaylistFactory.h"
#include "Interfaces/ICollectionController.h"
#include "CoreData/DataItem.h"
#include "CoreData/Item.h"
#include "CoreData/Media.h"
#include "Interfaces/IMediaCollection.h"
#include "Interfaces/ICore.h"
#include "JSONSerializer.h"
#include <QJsonObject>
#include "Interfaces/IPlaybackController.h"
#include <QDebug>
#include <QMutexLocker>

using namespace Core;
PlaylistHelper* PlaylistHelper::instance = 0;
QMutex PlaylistHelper::mutex;

PlaylistHelper::PlaylistHelper(QWidget *parent) :
    QMainWindow(parent),
    versionID(-1)
{
    newPlaylist();
    connect(Core::ICore::playbackController(), SIGNAL(playlistChanged()), this, SLOT(playerHasNewPlaylist()));
}

PlaylistHelper *PlaylistHelper::getInstance()
{
    //qDebug()<<Q_FUNC_INFO;
    QMutexLocker locker(&mutex);

    if(!instance)
    {
        instance = new PlaylistHelper();
    }
    return instance;
}

void PlaylistHelper::newPlaylist()
{
    currentPlaylist = ICore::createPlaylist();
}

bool PlaylistHelper::appendItem(QString collection, int id, QString type)
{
    return insertItem(currentPlaylist->getSize()-1, collection, id, type);
}

bool PlaylistHelper::insertItem(int pos, QString collection, int id, QString type)
{
    IMediaCollection* coll = ICore::collectionController()->getMediaCollectionByHash(collection);
    Item* item;

    if(type == "org.safri.audio.song")
    {
        item = qobject_cast<Item*>(coll->getByID(DataItem::SONG, id));
    }
    else if(type == "org.safri.audio.artist")
    {
        item = qobject_cast<Item*>(coll->getByID(DataItem::ARTIST, id));
    }
    else if(type == "org.safri.audio.album")
    {
        item = qobject_cast<Item*>(coll->getByID(DataItem::ALBUM, id));
    }
    else if(type == "org.safri.audio.genre")
    {
        item = qobject_cast<Item*>(coll->getByID(DataItem::GENRE, id));
    }
    return insertItem(item, pos);
}

void PlaylistHelper::moveSong(int fromPos, int toPos)
{
    currentPlaylist->moveMedia(fromPos, toPos);
}

void PlaylistHelper::deleteItem(int pos)
{
    currentPlaylist->deleteMedia(pos);
}

void PlaylistHelper::setAsCurrent()
{
    Core::ICore::playbackController()->setPlaylist(currentPlaylist);
}

void PlaylistHelper::playItem(int index)
{
    QSharedPointer<Core::IPlaylist> playlist = Core::ICore::playbackController()->getPlaylist();
    Core::ICore::playbackController()->stopAction()->trigger();
    playlist->setCurrentMedia(index);
    Core::ICore::playbackController()->playAction()->trigger();
}

void PlaylistHelper::setShuffle(bool value)
{
    currentPlaylist->setShuffle(value);
}

int PlaylistHelper::getCurrentVersionID()
{
    return versionID;
}

int PlaylistHelper::getCurrentPlayingSongIndex()
{
    if(!Core::ICore::playbackController()->getPlaylist().isNull())
        return Core::ICore::playbackController()->getPlaylist()->getCurrentMediaPosition();
    return -2;
}

int PlaylistHelper::getCurrentPlaylistSize()
{
    if(!currentPlaylist.isNull())
        return currentPlaylist->getSize();
    else
        return -1;
}

QSharedPointer<IPlaylist> PlaylistHelper::getPlaylistInstance()
{
    return currentPlaylist;
}

bool PlaylistHelper::insertItem(Item *item, int pos)
{
    if(item)
    {
        if (pos == -1)
        {
            newPlaylist();
            pos = 0;
        }

        if (pos <= currentPlaylist->getSize() && pos >= 0)
        {
            QList<Item*> list;
            list.append(item);
            currentPlaylist->insertMediaAt(pos, list);
            return true;
        }
    }
    return false;
}


QJsonArray PlaylistHelper::getCurrentPlaylist()
{
    QJsonArray array;
    for(int i = 0; i < currentPlaylist->getSize(); i++)
    {
        array.append(JSONSerializer::getMedia(currentPlaylist->getMediaAt(i)));
    }
    return array;
}

QJsonArray PlaylistHelper::getPlayingPlaylist()
{
    QSharedPointer<Core::IPlaylist> playlist = Core::ICore::playbackController()->getPlaylist();
    if(!playlist.isNull())
    {
        currentPlaylist = playlist;
        QJsonArray array;
        for(int i = 0; i < playlist->getSize(); i++)
        {
            array.append(JSONSerializer::getMedia(playlist->getMediaAt(i)));
        }
        return array;
    }
    else
    {
        return QJsonArray();
    }
}

void PlaylistHelper::playlistDataChanged()
{
    QMutexLocker locker(&mutex);
    ++versionID;
    //qDebug()<<Q_FUNC_INFO<<" "<<versionID;
}

void PlaylistHelper::playerHasNewPlaylist()
{
    connect(Core::ICore::playbackController()->getPlaylist().data(), SIGNAL(PlaylistEdited()), this, SLOT(playlistDataChanged()));
    playlistDataChanged();
   // qDebug()<<"NEW PLAYLIST";
}
