#include "SongtreeHelper.h"
#include "Songtree/CoreItemTypes/artistitemtype.h"
#include "Songtree/CoreItemTypes/albumitemtype.h"
#include "Songtree/CoreItemTypes/songitemtype.h"
#include "Songtree/CoreItemTypes/mediacollectionitemtype.h"
#include "Songtree/CoreItemTypes/genreitemtype.h"
#include "Interfaces/ICollectionController.h"
#include "PlaylistHelper.h"
#include <QJsonArray>
#include "icore.h"
#include "JSONSerializer.h"
#include <QDebug>

using namespace  Core;


SongtreeHelper::SongtreeHelper(QByteArray sessionID, QObject *parent) :
    QObject(parent), currentTree(0), idCounter(0), parentSession(sessionID)
{
    buildNewTree();
}

SongtreeHelper::~SongtreeHelper()
{
    if(currentTree)
    delete currentTree;
    for(int i = 0; i < treeHierarchy->size(); i++)
    {
        delete treeHierarchy->at(i);
    }

    delete treeHierarchy;
    qDebug()<<"DESTRUKTOR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
}

void SongtreeHelper::buildNewTree()
{
    treeHierarchy = new QList<ITreeItemType*>();
    treeHierarchy->append(new GenreItemType());
    treeHierarchy->append(new ArtistItemType());
    treeHierarchy->append(new AlbumItemType());
    treeHierarchy->append(new SongItemType());

    if(currentTree)
    {
        delete currentTree;
        currentTree = 0;
    }

    ICollectionController* collController = ICore::collectionController();
    QList<IMediaCollection*> mediaColl = collController->getCollections("org.safri.collection.audio");
    for (int i = 0; i < mediaColl.size(); i++)
    {
        IAudioCollection* tempAudioColl = qobject_cast<IAudioCollection*>(mediaColl.at(i));
        if(tempAudioColl)
        {
            audioCollMap.insert(tempAudioColl->getDatabaseLocation(), tempAudioColl);
        }
    }

    QList<Song*> songList;
    QList<IAudioCollection*> audioCollList = audioCollMap.values();
    for(int i = 0 ; i < audioCollList.size(); i++)
    {
        songList.append(audioCollList.at(i)->getSongs());
    }

    currentTree = new SongTree(songList, treeHierarchy);
}


QJsonArray SongtreeHelper::getRootNodes()
{
    return getChilds(-1);
}

QJsonArray SongtreeHelper::getChilds(int id)
{
    const SongTreeItem* node = 0;
    if( id == -1)
    {
        node = currentTree->getRootNode();
    }
    else if(itemMap.contains(id))
    {
        node = itemMap.value(id);
    }
    else
        return QJsonArray();

    QList<SongTreeItem*> childs;
    childs = node->getChilds();

    QJsonArray array;
    for(int i = 0; i < childs.size(); i++)
    {
        SongTreeItem* item = childs.at(i);
        int id = idMap.value(item, -1);
        if(id < 0)
        {
            id = idCounter;
            idMap.insert(item, id);
            itemMap.insert(id, item);
            idCounter++;
        }
        array.append(JSONSerializer::getSongTreeItemForJsTree(item, id));
    }
    return array;
}

QJsonArray SongtreeHelper::addToPlaylist(int nodeId, int pos)
{
    QJsonArray array;
    SongTreeItem* item = itemMap.value(nodeId, 0);
    if(item)
    {
        PlaylistHelper::getInstance()->insertItem(item, pos);
    }
    QList<Media*> media = item->getMedia();
    for(int i = 0; i < media.size(); i++)
    {
        array.append(JSONSerializer::getMedia(media.at(i)));
    }
    return array;
}

void SongtreeHelper::sessionExpired(QByteArray id)
{
    if(id == parentSession)
        delete this;
}
