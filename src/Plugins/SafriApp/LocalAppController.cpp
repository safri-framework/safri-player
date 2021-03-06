#include "LocalAppController.h"
#include <QDebug>
#include <QList>

#include "Interfaces/ICore.h"
#include "Interfaces/ICollectionController.h"
#include "Interfaces/IAudioCollection.h"
#include "Interfaces/IPlaybackController.h"
#include "Songtree/SongTree.h"
#include "Songtree/SongTreeModel.h"
#include "Songtree/SongTreeItem.h"
#include "Interfaces/ITreeItemType.h"
#include "Interfaces/IPlaylist.h"

#include "Songtree/CoreItemTypes/ArtistItemType.h"
#include "Songtree/CoreItemTypes/AlbumItemType.h"
#include "Songtree/CoreItemTypes/SongItemType.h"
#include "Songtree/CoreItemTypes/MediaCollectionItemType.h"
#include "Songtree/CoreItemTypes/GenreItemType.h"

#include "playlistmodel.h"

LocalAppController::LocalAppController(QObject *parent) :
    IAppController(parent), playlist(0), playlistModel(0), treeHierarchy(0), model(0), coverModel(0), songTree(0), coverSongTree(0)
{

    playlistModel = new PlaylistModel(Core::ICore::createPlaylist(), this);
    Q_EMIT newPlaylistModel();

    connect(Core::ICore::playbackController(), SIGNAL(playlistChanged()),this, SLOT(pbControllerHasNewPlaylist()));
}

QAbstractItemModel *LocalAppController::getSongtreeModel(TREE_HIERARCHY hierarchy)
{
    QMap<QUrl, Core::IAudioCollection*> audioCollMap;
    QList<Core::Song*> songList;

    Core::ICollectionController* collController = Core::ICore::collectionController();
    QList<Core::IMediaCollection*> mediaColl = collController->getCollections("org.safri.collection.audio");
    for (int i = 0; i < mediaColl.size(); i++)
    {
        Core::IAudioCollection* tempAudioColl = qobject_cast<Core::IAudioCollection*>(mediaColl.at(i));
        if(tempAudioColl)
        {
            audioCollMap.insert(tempAudioColl->getDatabaseLocation(), tempAudioColl);
        }
    }
    QList<Core::IAudioCollection*> audioCollList = audioCollMap.values();
    for(int i = 0 ; i < audioCollList.size(); i++)
    {
        songList.append(audioCollList.at(i)->getSongs());
    }


    if(songTree)
        delete songTree;


    songTree = new Core::SongTree(songList, createTreeHierachy(hierarchy));

    for(int i = 0 ; i < audioCollList.size(); i++)
    {
        connect(audioCollList.at(i), SIGNAL(itemAdded(Core::DataItem*)), songTree, SLOT(addItem(Core::DataItem*)));
    }

    if(model)
        delete model;

    model = new SongTreeModel(songTree, this);
    return model;
}

QAbstractItemModel *LocalAppController::getPlaylistModel()
{
    return playlistModel;
}

QAbstractItemModel *LocalAppController::getCoverModel()
{
    qDebug()<<"GETCOVERMODEL";
    QMap<QUrl, Core::IAudioCollection*> audioCollMap;
    QList<Core::Song*> songList;

    Core::ICollectionController* collController = Core::ICore::collectionController();
    QList<Core::IMediaCollection*> mediaColl = collController->getCollections("org.safri.collection.audio");
    for (int i = 0; i < mediaColl.size(); i++)
    {
        Core::IAudioCollection* tempAudioColl = qobject_cast<Core::IAudioCollection*>(mediaColl.at(i));
        if(tempAudioColl)
        {
            audioCollMap.insert(tempAudioColl->getDatabaseLocation(), tempAudioColl);
        }
    }
    QList<Core::IAudioCollection*> audioCollList = audioCollMap.values();
    for(int i = 0 ; i < audioCollList.size(); i++)
    {
        songList.append(audioCollList.at(i)->getSongs());
    }


    if(coverSongTree)
        delete coverSongTree;


    coverSongTree = new Core::SongTree(songList, createTreeHierachy(ALBUM));

    for(int i = 0 ; i < audioCollList.size(); i++)
    {
        connect(audioCollList.at(i), SIGNAL(itemAdded(Core::DataItem*)), coverSongTree, SLOT(addItem(Core::DataItem*)));
    }

    if(coverModel)
        delete coverModel;

    coverModel = new SongTreeModel(coverSongTree, this);
    return coverModel;
}



void LocalAppController::moveMediaInPlaylist(int from, int to)
{
    if (playlist != 0)
    {
        playlist->moveMedia(from, to);
    }
}

void LocalAppController::playTreeModelIndex(QModelIndex treeIndex)
{

    if (playlistModel)
    {
        delete playlistModel;
        playlistModel = 0;
    }

    Core::SongTreeItem* item = static_cast<Core::SongTreeItem*>(treeIndex.internalPointer());
    QList<Core::Item*> items;
    items.append(static_cast<Core::Item*>(item));

    playlist = Core::ICore::createPlaylist();
    playlist->insertMediaAt(0, items);

    Core::IPlaybackController* playbackController = Core::ICore::playbackController();

    playbackController->stopAction()->trigger();
    playbackController->setPlaylist(playlist);
    playbackController->playAction()->trigger();


}

void LocalAppController::enqueueTreeModelIndex(QModelIndex treeIndex)
{
    if (!playlistModel)
    {
        playlistModel = new PlaylistModel(playlist, this);
    }

    Core::SongTreeItem* item = static_cast<Core::SongTreeItem*>(treeIndex.internalPointer());
    QList<Core::Item*> items;
    items.append(static_cast<Core::Item*>(item));

    if(playlist.isNull())
        playlist = Core::ICore::createPlaylist();

    playlist->insertMediaAt(playlist->getSize(), items);
}

void LocalAppController::playPlaylistIndex(int index)
{
    if (index < playlist->getSize())
    {
        playlist->setCurrentMedia(index);
        Core::IPlaybackController* playbackConntroller = Core::ICore::playbackController();
        playbackConntroller->stopAction()->trigger();
        playbackConntroller->setPlaylist(playlist);
        playbackConntroller->playAction()->trigger();
    }
}

void LocalAppController::removeIndexFromPlaylist(int index)
{
    if(index < playlist->getSize())
        playlist->deleteMedia(index);
}

void LocalAppController::setShuffle(bool enabled)
{
    playlist->setShuffle(enabled);
}

IAppController::APP_MODE LocalAppController::getMode()
{
    return IAppController::LOCAL;
}

void LocalAppController::shutdown()
{
    // unused
}

QList<Core::ITreeItemType *> *LocalAppController::createTreeHierachy(TREE_HIERARCHY hierarchy)
{


    if(treeHierarchy)
    {
        for(int i = 0; i < treeHierarchy->size(); i++)
        {
            delete treeHierarchy->at(i);
        }
        delete treeHierarchy;
        treeHierarchy = 0;
    }

    treeHierarchy = new QList<ITreeItemType*>();

    switch(hierarchy)
    {
        case IAppController::GENRE:
            treeHierarchy->append(new GenreItemType());
            treeHierarchy->append(new ArtistItemType());
            treeHierarchy->append(new AlbumItemType());
            treeHierarchy->append(new SongItemType());
            break;

        case IAppController::ARTIST:
            treeHierarchy->append(new ArtistItemType());
            treeHierarchy->append(new AlbumItemType());
            treeHierarchy->append(new SongItemType());
            break;

        case IAppController::ALBUM:
            treeHierarchy->append(new AlbumItemType());
            treeHierarchy->append(new SongItemType());
            break;
    }
    return treeHierarchy;
}


void LocalAppController::pbControllerHasNewPlaylist()
{
    if (playlistModel)
    {
        delete playlistModel;
    }

    playlist = Core::ICore::playbackController()->getPlaylist();
    playlistModel = new PlaylistModel(playlist, this);
    Q_EMIT newPlaylistModel();
}
