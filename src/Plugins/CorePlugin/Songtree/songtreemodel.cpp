#include "songtreemodel.h"
#include <QFlags>
#include <assert.h>
#include <QDebug>

#include <QUrl>
#include <QIcon>
#include <QImage>

/**
#include "databasedao.h"
**/

#include "../CoreData/song.h"
#include "../CoreData/dataitem.h"
#include "../icore.h"


SongTreeModel::SongTreeModel(SongTree* songTree, QObject *parent) :
    QAbstractItemModel(parent), songTree(songTree)
{

    // QObject reparenting, to automatically delete the song tree
    // if the model gets deleted
    songTree->setParent(this);



    //this->setSupportedDragActions(Qt::drag);

    //connect(songTree, SIGNAL(itemInserted(SongTreeItem*,int)), this, SLOT(insertItem(SongTreeItem*,int)));
    //connect(songTree, SIGNAL(itemRemoved(SongTreeItem*,int)), this, SLOT(removeItem(SongTreeItem*,int)));

    connect(songTree, SIGNAL(beginMoveItem(SongTreeItem*,int,SongTreeItem*,int)), this, SLOT(beginMoveItem(SongTreeItem*,int,SongTreeItem*,int)));
    connect(songTree, SIGNAL(endMoveItem(SongTreeItem*)), this, SLOT(endMoveItem(SongTreeItem*)));
    connect(songTree, SIGNAL(beginInsertItem(SongTreeItem*,int)), this, SLOT(beginInsertItem(SongTreeItem*,int)));
    connect(songTree, SIGNAL(endInsertItem()), this, SLOT(endInsertItem()));
    connect(songTree, SIGNAL(beginRemoveItem(SongTreeItem*,int)), this, SLOT(beginRemoveItem(SongTreeItem*,int)));
    connect(songTree, SIGNAL(endRemoveItem()), this, SLOT(endRemoveItem()));
}

Qt::ItemFlags SongTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
    {
        SongTreeItem* item = static_cast<SongTreeItem*>(index.internalPointer());
        DataItem* dataItemPtr = item->getDataItemPtr();

        if( dataItemPtr != 0 && dataItemPtr->getType() == DataItem::SONG )
        {
            return Qt::ItemIsDragEnabled | Qt::ItemIsEditable | defaultFlags;
        }
        else
        {
            return Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsEditable | defaultFlags ;
        }

    }
    else
    {
        return defaultFlags ;
    }
}

Qt::DropActions SongTreeModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}
Qt::DropActions SongTreeModel::supportedDragActions () const
{
    return Qt::CopyAction;
}



QMimeData *SongTreeModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    QList<QUrl> urlList;

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            qint64 pointer = (qint64) index.internalPointer();


            QString text = data(index, Qt::DisplayRole).toString();
            stream <<  pointer ;

            SongTreeItem* item = (SongTreeItem*) index.internalPointer();
            QList<Song*> songlist = item->getSongs();


            for (int i = 0; i < songlist.size(); i++)
            {
                urlList.append(QUrl::fromLocalFile(songlist.at(i)->getFileName()));

            }


        }
    }

    mimeData->setData("Item", encodedData);
    mimeData->setUrls(urlList);
    return mimeData;

}








bool SongTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(column)
    SongTreeItem* item  = (SongTreeItem*) parent.internalPointer();




    if (parent.isValid())
    {


        if (action == Qt::IgnoreAction)
            return true;

        if (!data->hasFormat("Item"))
            return false;

        int beginRow;
        Q_UNUSED(beginRow)

        if (row != -1)
            beginRow = row;
        else if (parent.isValid())
            beginRow = 0;
        else
            beginRow = rowCount(QModelIndex());

        QByteArray encodedData = data->data("Item");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        QList<SongTreeItem*> draggedItems;
        QList<SongTreeItem*> actuallyDraggedItems;

        while (!stream.atEnd()) {
            qint64 pointer;
            stream >> pointer ;
            //newItems[id][row][column] = text;
            SongTreeItem* item = (SongTreeItem*) pointer;
            draggedItems.append(item);

        }




        SongTreeItem *droppTargetItem = item;
        //qDebug()<< BaseDTO::typeToString(droppTargetItem->getDTOPtr()->getType());

       // QList<Item*> songList;
        SongTreeItem* draggedItem;
        for (int i = 0; i < draggedItems.size(); i++)
        {
            draggedItem = draggedItems.at(i);
            if ( (!draggedItem->hasParentRelation(item)) && draggedItem != item)
            {
                //songList.append(draggedItem->getSongs());
                actuallyDraggedItems.append(draggedItem);
            }
        }


        /*
        QString artist;
        QString genre;
        QString album;


        // Find out the new attributes for the dragged Items

        while (item->getParentItem() != 0)
        {

            QString type = item->getTypeName();
            if (type == "ArtistType")
            {
                artist = item->getDTOPtr()->getName();
                //artist = item->getName();
            }
            if (type == "AlbumType")
            {
                album = item->getDTOPtr()->getName();
            }
            if (type == "GenreType")
            {
                genre = item->getDTOPtr()->getName();
            }

            item = item->getParentItem();
        }


        qDebug()<<artist<<"  "<<album<<"  "<<genre;
        for (int i = 0; i < songList.size(); i++)
        {

           // change settings in underlying data structure
           Q_EMIT songAttributesChanged(songList.at(i), artist, album, genre);

        }
        */




        qDebug() << "Bis hierher?";

        QList<SongTreeItem*> previousParents;

        for (int i = 0; i < actuallyDraggedItems.size(); i++)
        {
            SongTreeItem* source = actuallyDraggedItems.at(i);
            previousParents.append(source->getParentItem());
            songTree->move(source, droppTargetItem);
        }

        //Q_EMIT dragAndDropOperation(actuallyDraggedItems, previousParents, droppTargetItem );

        /*
        for (int i = 0; i < songList.size(); i++)
        {


           songTree->addSong(songList.at(i));

        }

        for (int i = 0; i < actuallyDraggedItems.size(); i++)
        {
            SongTreeItem* item = actuallyDraggedItems.at(i);
            item->remove();
        }
        */


        Q_EMIT dropOperationOccured();
        return true;
    }
    else
    {
        return false;
    }
}





QStringList SongTreeModel::mimeTypes() const
{
    QStringList types;
    types << "Item";
    return types;
}

int SongTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

int SongTreeModel::rowCount(const QModelIndex &parent) const
{
    const SongTreeItem* parentItem;

    if (!parent.isValid())
    {
        // for the invalid model index the item is the
        // root of the song tree
        parentItem = songTree->getRootNode();
    }
    else
    {
        parentItem = static_cast<SongTreeItem*>(parent.internalPointer());
    }

    assert(parentItem != 0);

    return parentItem->getNumberOfChilds();
}

QModelIndex SongTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    SongTreeItem* childItem = static_cast<SongTreeItem*>(index.internalPointer());
    SongTreeItem* parentItem = childItem->getParentItem();

    if (parentItem == songTree->getRootNode())
    {
        return QModelIndex();
    }

    assert(parentItem != 0);

    return createIndex(parentItem->getRow(), 0, parentItem);
}



QVariant SongTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)

    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole )
    {
        return "";
    }

    return QVariant();
}




QVariant SongTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    SongTreeItem* item = static_cast<SongTreeItem*>(index.internalPointer());
    DataItem* dataItemPtr = item->getDataItemPtr();

    assert(item != 0);

    QString tooltipText;
    switch (role)
    {
        case Qt::DisplayRole:

            if (dataItemPtr && dataItemPtr->getType() == DataItem::ALBUM)
            {
                Album *album = static_cast<Album*>(dataItemPtr);

                if (album->isCompilation())
                {
                    return item->getName() + " (Compilation)";
                }
            }

            return item->getName();

        case Qt::UserRole:
            return item->getSongs().size();


        case coverRole:
        /*
            if (dataItemPtr != 0 && dataItemPtr->getType() == DataItem::ALBUM)
            {
                Album* album = (Album*) dataItemPtr;
                return QString("file://") + album->getCoverFile();
            }
            else
            {
                return QVariant();
            }
            */
        if (dataItemPtr != 0 && dataItemPtr->getType() == DataItem::ALBUM)
        {

            QString coverPath;
            coverPath = ICore::storageDirectory() + "/covers/" + QString::number(dataItemPtr->getID()) + ".jpg";
            QImage image(coverPath);
            if (image.isNull())
            {
                coverPath = "qrc:/images/ressources/default.png";
            }
            return QUrl::fromLocalFile(coverPath);
        }
        else
        {
            return QUrl();
        }
            break;

        case Qt::ToolTipRole:
            return item->getName();

            if (item->getDataItemPtr())
            {

                if (dataItemPtr != 0 && dataItemPtr->getType() == DataItem::SONG)
                {
                    Song* song = (Song*) item->getDataItemPtr();
                    tooltipText = song->getAlbum()->getName()+"\n";
                    tooltipText += song->getArtist()->getName()+"\n";
                    tooltipText += song->getGenre()->getName()+"\n";
                    return tooltipText;
                }

                if (item->getTypeName() == "AlbumType")
                {

                    tooltipText+="ARTISTS \n\n";
                    Album* album = (Album*) item->getDataItemPtr();
                    QList<Artist*> artists = album->getArtists();
                    for(int i = 0; i < artists.size(); i++)
                        tooltipText+= artists.at(i)->getName()+"\n";

                    tooltipText+="\n";
                    tooltipText+="SONGS \n\n";
                    QList<Song*> songs = album->getSongs();
                    for(int i = 0; i < songs.size(); i++)
                        tooltipText+= songs.at(i)->getArtist()->getName() + " - " + songs.at(i)->getName()+"\n";

                    tooltipText+="\n";
                    tooltipText+="ID: "+QString::number(album->getID());

                    return tooltipText;
                }

                if (item->getTypeName() == "ArtistType")
                {
                    tooltipText+="AlBEN \n\n";
                    Artist* artist = (Artist*) item->getDataItemPtr();
                    QList<Album*> album = artist->getAlbums();
                    for(int i = 0; i < album.size(); i++)
                        tooltipText+= album.at(i)->getName()+"\n";

                    tooltipText+="\n";

                    tooltipText+="ID: "+QString::number(artist->getID());

                    return tooltipText;
                }

                if (item->getTypeName() == "GenreType")
                {
                    tooltipText+="SONGS \n\n";
                    Genre* genre = (Genre*) item->getDataItemPtr();
                    QList<Song*> song = genre->getSongs();
                    for(int i = 0; i < song.size(); i++)
                        tooltipText+= song.at(i)->getName()+"\n";

                    tooltipText+="\n";

                    return tooltipText;
                }


            }
            break;

        case Qt::DecorationRole:


            if (dataItemPtr != 0 && dataItemPtr->getType() == DataItem::SONG)
            {
                return QIcon(":/icons/ressources/song_icon.png");
            }

            if (dataItemPtr != 0 && dataItemPtr->getType() == DataItem::ALBUM)
            {

                QString coverPath;
                coverPath = ICore::storageDirectory() + "/covers/" + QString::number(dataItemPtr->getID()) + ".jpg";
                QImage image(coverPath);
                if (image.isNull())
                {
                    image = QImage(":/images/ressources/default.png");
                }
                return image;
            }

            if (dataItemPtr != 0 && dataItemPtr->getType() == DataItem::ARTIST)
            {
                return QIcon(":/icons/ressources/artist_icon.png");
            }

            return QIcon(":/icons/ressources/music_icon.png");

        if (dataItemPtr != 0 && dataItemPtr->getType() == DataItem::ARTIST)
        {
            return "qrc:/icons/ressources/artist_icon.png";
        }

            return "qrc:/icons/ressources/music_icon.png";


        default:
            return QVariant();
    }

    return QVariant();
}

QModelIndex SongTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    const SongTreeItem* parentItem;

    if (!parent.isValid())
    {
        parentItem = songTree->getRootNode();
    }
    else
    {
        parentItem = static_cast<SongTreeItem*>(parent.internalPointer());
    }

    assert(parentItem != 0);

    SongTreeItem* childItem = parentItem->getChild(row);

    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }

}

QHash<int, QByteArray> SongTreeModel::roleNames() const
{

    QHash<int, QByteArray> roles;
    roles[iconRole] = "iconpath";
    roles[coverRole] = "albumCover";
    roles[Qt::DisplayRole] ="display";

    return roles;
}


void SongTreeModel::insertItem(SongTreeItem *parent, int row)
{
    QModelIndex parentIndex, newIndex;
    SongTreeItem* childItem;

    if (parent == 0)
    {
        parentIndex = QModelIndex();
        newIndex = index(row, 0, parentIndex);

        childItem = static_cast<SongTreeItem*>(newIndex.internalPointer());
    }
    else
    {
        parentIndex = getModelIndexForItem(parent);
        indexMap.insert(parent, parentIndex);

        newIndex = index(row, 0, parentIndex);
        childItem = static_cast<SongTreeItem*>(parentIndex.internalPointer())->getChild(row);
    }

    indexMap.insert(childItem, newIndex);

    //qDebug() << "beginInsertRows(" << parent->getName() << ", " << row << ")";
    beginInsertRows(parentIndex, row, row);

    endInsertRows();
}

void SongTreeModel::removeItem(SongTreeItem *parent, int row)
{
    QModelIndex parentIndex, indexRemoved;
    SongTreeItem* childItem;

    if (parent == 0)
    {
        parentIndex = QModelIndex();
        indexRemoved = index(row, 0, parentIndex);

        childItem = static_cast<SongTreeItem*>(indexRemoved.internalPointer());
    }
    else
    {
        parentIndex = indexMap.value(parent);

        indexRemoved = index(row, 0, parentIndex);
        //childItem = static_cast<SongTreeItem*>(parentIndex.internalPointer())->getChild(row);
    }

    childItem = indexMap.key(indexRemoved);
    indexMap.remove(childItem);

    beginRemoveRows(parentIndex, row, row);

    endInsertRows();
}

QModelIndex SongTreeModel::getModelIndexForItem(SongTreeItem *item)
{
    if (item == songTree->getRootNode())
    {
        return QModelIndex();
    }
    else
    {
        QModelIndex parentIndex = getModelIndexForItem(item->getParentItem());

        return index(item->getRow(), 0, parentIndex);
    }
}

void SongTreeModel::beginMoveItem(SongTreeItem *srcParent, int srcRow, SongTreeItem *destParent, int destRow)
{
    beginMoveRows(getModelIndexForItem(srcParent), srcRow, srcRow, getModelIndexForItem(destParent), destRow);
}

void SongTreeModel::endMoveItem(SongTreeItem *destParent)
{
    Q_UNUSED(destParent)
    endMoveRows();
}

void SongTreeModel::beginInsertItem(SongTreeItem *parent, int row)
{
    beginInsertRows(getModelIndexForItem(parent), row, row);
}

void SongTreeModel::endInsertItem()
{
    endInsertRows();
}

void SongTreeModel::beginRemoveItem(SongTreeItem *parent, int row)
{
    beginRemoveRows(getModelIndexForItem(parent), row, row);
}

void SongTreeModel::endRemoveItem()
{
    endRemoveRows();
}

QModelIndex SongTreeModel::artistIndex(int row)
{
    return index(row, 0);
}
