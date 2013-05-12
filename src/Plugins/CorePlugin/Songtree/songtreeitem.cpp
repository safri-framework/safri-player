#include "songtreeitem.h"
#include "songtree.h"
#include "changedflags.h"
#include "../CoreData/song.h"
#include "../CoreData/album.h"
#include <QDebug>

using namespace Core;

#ifdef DEBUG
        long SongTreeItem::idCount = 0;
#endif

SongTreeItem::SongTreeItem(ITreeItemType* type, int level, QList<ITreeItemType*>* hierarchy, SongTreeItem* parentItem, Song* song, SongTree* songTree, QObject *parent)
    : Item(parent), parentItem(parentItem), childs(new QList<SongTreeItem*>()), childMap(new QMap<QString, SongTreeItem*>()),
      dataItemPtr(type->getNodeDataItem(song)), name(type->getNodeName(song)), type(type), level(level), hierarchy(hierarchy), songTree(songTree), hash(type->getHash(song))
{
#ifdef DEBUG
        ID = idCount++;

        name = "ID(" +QString::number(ID) + ") " + name;
#endif
}

SongTreeItem::SongTreeItem(QList<ITreeItemType*>* hierarchy, SongTree* songTree, QObject *parent)
    : Item(parent), parentItem(0), childs(new QList<SongTreeItem*>()), childMap(new QMap<QString, SongTreeItem*>()),
      dataItemPtr(0), name("ROOT"), type(0), level(-1), hierarchy(hierarchy), songTree(songTree), hash("")
{
#ifdef DEBUG
        ID = idCount++;

        name = "ID(" +QString::number(ID) + ") " + name;
#endif
}

SongTreeItem::SongTreeItem(SongTreeItem *sample, SongTreeItem *parentItem, QObject *parent)
    : Item(parent), parentItem(parentItem), childs(new QList<SongTreeItem*>()), childMap(new QMap<QString, SongTreeItem*>()),
      dataItemPtr(sample->dataItemPtr), name(sample->name), type(sample->type), level(sample->level), hierarchy(sample->hierarchy), songTree(sample->songTree), hash(sample->hash)
{
#ifdef DEBUG
        ID = idCount++;

        name = "ID(" +QString::number(ID) + ") " + name;
#endif
}

bool SongTreeItem::ancestorsContains(QRegExp exp)
{
    SongTreeItem* temp = this;

    while(temp != 0)
    {
        if (temp->getName().contains(exp))
            return true;

        temp = temp->getParentItem();
    }

    return false;
}

void SongTreeItem::setDataItemPtr(DataItem *dataItemPtr)
{
    this->dataItemPtr = dataItemPtr;
}

bool SongTreeItem::subTreeContains(QRegExp exp)
{
    if (this->name.contains(exp))
        return true;

    for (int i = 0; i < childs->size(); i++)
    {
        if (this->childs->at(i)->subTreeContains(exp))
            return true;
    }

    return false;
}



QString SongTreeItem::getName()
{
    return name;
}

SongTreeItem* SongTreeItem::getParentItem() const
{
    return parentItem;
}

QList<Media *> SongTreeItem::getMedia()
{
    QList<Media*> media;
    QList<Song*> songs = this->getSongs();
    for(int i = 0; i < songs.size(); i++)
    {
        media.append(songs.at(i));
    }
    qDebug()<<"getMedia"<<media.size();
    return media;
}

void SongTreeItem::addSong(Song* song)
{
    int maxLevel = hierarchy->size() - 1;

    if (level == maxLevel)
    {
        // nothing to do on the maximum tree level (leaf)
        return;
    }

    SongTreeItem* nextItem = getOrInsertChildItem(song);

    nextItem->addSong(song);
}

QString SongTreeItem::getTypeName()
{
    return type->getTypeName();
}

int SongTreeItem::getNumberOfChilds() const
{
    return childs->size();
}

DataItem* SongTreeItem::getDataItemPtr()
{
    return this->dataItemPtr;
}

QList<Song*> SongTreeItem::getSongs()
{
    QList<Song*> list;

    if(this->dataItemPtr != 0 && this->dataItemPtr->getType() == DataItem::SONG)
    {
         list.append((Song*) this->dataItemPtr);
    }
    else
    {
        for (int i = 0; i < childs->size(); i++)
        {
            list.append(childs->at(i)->getSongs());
        }

    }

    return list;
}

void SongTreeItem::print()
{
    if (level >= 0)
    {
        QString tab;

        for (int i = 0; i < level; i++)
        {
            tab.append("\t");
        }

        qDebug() << tab << name;
    }

    for (int i = 0; i < childs->size(); i++)
    {
        childs->at(i)->print();
    }
}

int SongTreeItem::getRow()
{
    if (parentItem)
    {
        return parentItem->childs->indexOf(const_cast<SongTreeItem*>(this));
    }

    return 0;
}

SongTreeItem* SongTreeItem::getChild(int index) const
{
    if (index < childs->size() && index >= 0)
    {
        return childs->at(index);
    }
    else
    {
        qDebug() << "SongTreeItem::getChild(): QList::at() out of range.";
    }

    return 0;
}

SongTreeItem::~SongTreeItem()
{
    delete childs;
    delete childMap;
}


void SongTreeItem::removeSubtree()
{
    for (int i = 0; i < this->getNumberOfChilds(); i++)
    {
        getChild(i)->removeSubtree();
    }

    int rowRemoved = parentItem->childs->indexOf(this);

    songTree->emitBeginRemoveItem(parentItem, rowRemoved);

        parentItem->childs->removeAt(rowRemoved);
        parentItem->childMap->remove(parentItem->childMap->key(this));

    songTree->emitEndRemoveItem();
}

int SongTreeItem::getTreeLevel()
{
    return level;
}

void SongTreeItem::remove(SongTreeItem *sender)
{
    if (sender == 0)
    {
        parentItem->remove(this);
    }
    else
    {
        int rowRemoved = childs->indexOf(sender);

        songTree->emitBeginRemoveItem(this, rowRemoved);

            childs->removeAt(rowRemoved);
            childMap->remove( childMap->key(sender) );

        songTree->emitEndRemoveItem();

        if (childs->size() < 1)
        {
            if (parentItem != 0)
            {
                parentItem->remove(this);
            }
            else
            {
                //songTree->emitItemRemoved(0, rowRemoved);
                // remove 0/rowRemoved
            }
        }
        else
        {

            //songTree->emitItemRemoved(this, rowRemoved);
            // remove this/rowRemoved
        }
    }
}

bool SongTreeItem::hasParentRelation(SongTreeItem *other)
{
    SongTreeItem* checkItem = parentItem;

    do
    {
        if (checkItem == other)
        {
            return true;
        }

        checkItem = checkItem->parentItem;
    }
    while (checkItem != 0);

    return false;
}

void SongTreeItem::moveToParent(SongTreeItem *destination)
{
    SongTreeItem *upperLevelItem, *source, *childItem;

    source = this;

    // if source and destination are not below the same costum type (e.g. they are in different decades)
    if (!checkForEqualCostumType(destination))
    {
        // don't move the item
        return;
    }

    if ( (source->level - 1) == destination->level )
    {
        qDebug()<<"3";

        QString key;

        if (destination->useHash())
        {
            key = source->hash;
        }
        else
        {
            key = source->name;
        }

        SongTreeItem *destinationChild = destination->childMap->value(key);

        //destinationChild = 0;

        if (destinationChild != 0)
        {
            QList<SongTreeItem*> childsTemp = QList<SongTreeItem*>(*source->childs);
            int childCount = childsTemp.size();

            for (int i = 0; i < childCount; i++)
            {
                childsTemp.at(i)->moveToParent(destinationChild);
            }
            return;
        }
        else
        {

            // move complete source item to destination

            SongTreeItem *sourceParent = source->parentItem;

            // remove source item from sourceParent item
            int rowRemoved = sourceParent->childs->indexOf(source);

            songTree->emitBeginMoveItem(sourceParent, rowRemoved, destination, destination->childs->size());

                sourceParent->childs->removeAt(rowRemoved);
                sourceParent->childMap->remove( sourceParent->childMap->key(source) );

                if (sourceParent->dataItemPtr != 0 && sourceParent->dataItemPtr->getType() == DataItem::ALBUM)
                {
                    Album *album = static_cast<Album*>(sourceParent->dataItemPtr);

                    if (album->isCompilation() && sourceParent->childs->size() == 0)
                    {
                        Album *newAlbum = new Album(album, album->parent());
                        sourceParent->dataItemPtr = newAlbum;
                    }

                    // WENN HIER COMPILATION, ABER VON EINEM INTERPRET KEIN SONG MEHR
                }


                // set new parent item for source item
                source->parentItem = destination;

                // insert the source into the destination item
                //destination->childMap->insert(source->name, source);
                destination->childs->append(source);

                ChangedFlags flags;

                destination->adaptParentDataToSource(source, flags);

                if (destination->useHash())
                {
                    destination->childMap->insert(source->hash, source);
                }
                else
                {
                    destination->childMap->insert(source->name, source);
                }


            songTree->emitEndMoveItem(destination);
            return;
        }
    }

    if ( (source->level - 1) > destination->level )
    {
        qDebug()<<"2";
        // parentUp counts how many levels we must ascent from the
        // source item to get to the item one level below the destination level
        int parentUp = source->level - destination->level - 1;

        upperLevelItem = source;
        for (int i = 0; i < parentUp; i++)
        {
            upperLevelItem = upperLevelItem->parentItem;
        }

        // upperLevelItem now contains the item up from the source which is
        // one level below the destination level

        // we must now check if the destination item contains already an item
        // for the meant upperLevelItem - otherwise insert it

        childItem = destination->getOrInsertChildItem(upperLevelItem);

        moveToParent(childItem);
    }



    if ((source->level - 1) < destination->level )
    {
        int childs = source->getNumberOfChilds();
        for (int i = 0; i < childs; i++)
        {
            source->getChild(0)->moveToParent(destination);
        }
        source->removeSubtree();
    }
}

QList<SongTreeItem *> SongTreeItem::getChilds() const
{
    QList<SongTreeItem*> childs;
    childs = QList<SongTreeItem*>(*this->childs);
    return childs;
}

SongTreeItem* SongTreeItem::getOrInsertChildItem(Song *song)
{
    int maxLevel = hierarchy->size() - 1;

    ITreeItemType* nextLevelType;

    nextLevelType = hierarchy->at(level+1);
    SongTreeItem* nextItem;

    QString newItemName;

    /*
    if (this->type == 0 || type->allowsChildNameDuplicates())
    {
        newItemName = nextLevelType->getHash(song);
    }
    else
    {
        newItemName = nextLevelType->getNodeName(song);
    }
    */

    if (useHash())
    {
        newItemName = nextLevelType->getHash(song);
    }
    else
    {
        newItemName = nextLevelType->getNodeName(song);
    }

    //newItemName = nextLevelType->getHash(song);
    //newItemName = nextLevelType->getNodeName(song);

    if (level == maxLevel - 1)
    {
        nextItem = 0;
    }
    else
    {
        nextItem = childMap->value(newItemName);
    }

    if (nextItem == 0)
    {
        nextItem = new SongTreeItem(nextLevelType, level+1, hierarchy, this, song, songTree, this);


        songTree->emitBeginInsertItem(this, childs->size());

            childMap->insert(newItemName, nextItem);
            childs->append(nextItem);

        songTree->emitEndInsertItem();

    }

    return nextItem;
}

SongTreeItem * SongTreeItem::getOrInsertChildItem(SongTreeItem *sampleItem)
{
    int maxLevel = hierarchy->size() - 1;

    ITreeItemType* nextLevelType;
    Q_UNUSED(nextLevelType)

    nextLevelType = hierarchy->at(level+1);
    SongTreeItem* nextItem;

    QString newItemName;

    /*
    if (this->type == 0 || type->allowsChildNameDuplicates())
    {
        newItemName = sampleItem->hash;
    }
    else
    {
        newItemName = sampleItem->name;
    }
    */

    // newItemName = sampleItem->hash;

    if (this->useHash())
    {
        newItemName = sampleItem->hash;
    }
    else
    {
        newItemName = sampleItem->name;
    }

    if (level == maxLevel - 1)
    {
        nextItem = 0;
    }
    else
    {
        nextItem = childMap->value(newItemName);
    }

    if (nextItem == 0)
    {
        nextItem = new SongTreeItem(sampleItem, this, this);

        songTree->emitBeginInsertItem(this, childs->size());

            childMap->insert(newItemName, nextItem);
            childs->append(nextItem);

        songTree->emitEndInsertItem();
    }

    return nextItem;
}

void SongTreeItem::adaptParentDataToSource(SongTreeItem *source, ChangedFlags &flags)
{

    if (this->getParentItem() != songTree->getRootNode())
    {
        this->getParentItem()->adaptParentDataToSource(source, flags);
    }

    QList<Song*> songs = source->getSongs();
    int songCount = songs.size();

    // ignore TreeItemTypes which doesn't match to a specific DataItem
    if (this->dataItemPtr != 0)
    {
        switch (this->dataItemPtr->getType())
        {
            case DataItem::GENRE:

                for (int i = 0; i < songCount; i++)
                {
                    qDebug() << songs.at(i)->getName() << " moveToGenre " << this->dataItemPtr->getName();
                    songs.at(i)->moveToGenre(this->dataItemPtr);
                }
                flags.genreChanged = true;
                flags.genre = static_cast<Genre*>(this->dataItemPtr);
                break;

            case DataItem::ALBUM:

                for (int i = 0; i < songCount; i++)
                {
                    songs.at(i)->moveToAlbum(this->dataItemPtr);
                    qDebug() << songs.at(i)->getName() << " moveToAlbum " << this->dataItemPtr->getName();
                }
                flags.albumChanged = true;
                flags.album = static_cast<Album*>(this->dataItemPtr);
            break;

            case DataItem::ARTIST:

                for (int i = 0; i < songCount; i++)
                {
                    songs.at(i)->moveToArtist(this->dataItemPtr);
                    qDebug() << songs.at(i)->getName() << " moveToArtist " << this->dataItemPtr->getName();
                }
                flags.artistChanged = true;
                flags.artist = static_cast<Artist*>(this->dataItemPtr);
                break;

            default:
                break;
        }
    }
}



bool SongTreeItem::useHash()
{

    for (int i = 0; i <= level; i++)
    {
        ITreeItemType *itemType = hierarchy->at(i);
        if (itemType->getTypeName() == "ArtistType")
        {
            return false;
        }
    }

    return true;
}

bool SongTreeItem::checkForEqualCostumType(SongTreeItem *destination)
{
    SongTreeItem *source = this;

    for (int i = 0; i <= source->level; i++)
    {
        ITreeItemType *itemType = hierarchy->at(i);
        if (itemType->getTypeName() == "DecadeType")
        {
            if (destination->level < i)
            {
                return true;
            }

            SongTreeItem *sourceCostumParent = source;
            while (sourceCostumParent->level > i)
            {
                sourceCostumParent = sourceCostumParent->parentItem;
            }

            SongTreeItem *destinationCostumParent = destination;
            while (destinationCostumParent->level > i)
            {
                destinationCostumParent = destinationCostumParent->parentItem;
            }

            if (sourceCostumParent->hash == destinationCostumParent->hash)
            {
                return true;
            }
            else
            {
                return false;
            }

        }
    }

    return true;
}

