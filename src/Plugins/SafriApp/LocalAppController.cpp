#include "LocalAppController.h"

#include <QList>

#include "icore.h"
#include "Interfaces/ICollectionController.h"
#include "Interfaces/IAudioCollection.h"
#include "iplaybackcontroller.h"
#include "Songtree/songtree.h"
#include "Songtree/songtreemodel.h"
#include "Songtree/songtreeitem.h"
#include "Interfaces/itreeitemtype.h"
#include "iplaylist.h"

#include "Songtree/CoreItemTypes/artistitemtype.h"
#include "Songtree/CoreItemTypes/albumitemtype.h"
#include "Songtree/CoreItemTypes/songitemtype.h"
#include "Songtree/CoreItemTypes/mediacollectionitemtype.h"
#include "Songtree/CoreItemTypes/genreitemtype.h"

#include "playlistmodel.h"

LocalAppController::LocalAppController(QObject *parent) :
    IAppController(parent), songTree(0), playlist(0), playlistModel(0)
{
}

QAbstractItemModel *LocalAppController::getSongtreeModel()
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

    songTree = new Core::SongTree(songList, createTreeHierachy());

    for(int i = 0 ; i < audioCollList.size(); i++)
    {
        connect(audioCollList.at(i), SIGNAL(itemAdded(Core::DataItem*)), songTree, SLOT(addItem(Core::DataItem*)));
    }

    return new SongTreeModel(songTree, this);
}

QAbstractItemModel *LocalAppController::getPlaylistModel()
{
    return playlistModel;
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

    playlistModel = new PlaylistModel(playlist, this);
}

QList<Core::ITreeItemType *> *LocalAppController::createTreeHierachy()
{
    QList<Core::ITreeItemType *> *treeHierarchy;

    treeHierarchy = new QList<ITreeItemType*>();
    treeHierarchy->append(new GenreItemType());
    treeHierarchy->append(new ArtistItemType());
    treeHierarchy->append(new AlbumItemType());
    treeHierarchy->append(new SongItemType());

    return treeHierarchy;
}