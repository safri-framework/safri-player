#include "SafedPlaylistModel.h"
#include "m3utranslator.h"
#include <QIcon>
#include <QFileInfo>
#include <QImage>

SafedPlaylistModel::SafedPlaylistModel(QObject *parent) :
    QAbstractItemModel(parent)
{

    rootItem = M3uTranslator::getPlaylistTree();



}


QModelIndex SafedPlaylistModel::index(int row, int column, const QModelIndex& parent) const
{

    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());


    TreeItem *childItem = parentItem->getChilds()->at(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();


}

QModelIndex SafedPlaylistModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->getParent();

    if (parentItem == rootItem)
        return QModelIndex();

   int parentRow =  rootItem->getChilds()->indexOf(parentItem);

    return createIndex(parentRow, index.column(), parentItem);

}



int SafedPlaylistModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
             return 0;

         if (!parent.isValid())
             parentItem = rootItem;
         else
             parentItem = static_cast<TreeItem*>(parent.internalPointer());


         return parentItem->getChilds()->size();
}

QVariant SafedPlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole )
    {

        switch (section)
        {

            case 0:
                return "Gespeicherte Playlisten";

            case 1:
                return "Tracks";

        }
    }

    return QVariant();
}




int SafedPlaylistModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant SafedPlaylistModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
             return QVariant();

     TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
     if (role == Qt::DisplayRole)
     {

         return item->getText();
     }
     if(role == Qt::DecorationRole)
     {

        if (item->getType() =="PLAYLIST")
        {

            return QIcon("img/music_icon.png");

        }
        if (item->getType() == "SONG")
        {

           return QIcon("img/song_icon.png");

        }

     }

  return QVariant();
}

Qt::DropActions SafedPlaylistModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags SafedPlaylistModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}


QStringList SafedPlaylistModel::mimeTypes() const
{
    QStringList types = QAbstractItemModel::mimeTypes();
    types << "text/uri-list";

    return types;
}


bool SafedPlaylistModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
//    bool dropped = false;
//if(pl)

//    if (action == Qt::MoveAction)
//    {

//        if (data->hasFormat("application/x-qabstractitemmodeldatalist"))
//        {

//            QByteArray encoded = data->data("application/x-qabstractitemmodeldatalist");
//            QDataStream stream(&encoded, QIODevice::ReadOnly);

//            int sourceRow;

//            stream >> sourceRow;

//            int insertLocation;

//            if ( parent.isValid() )
//            {
//                // if something dropped on a song, use the location of the valid ModelIndex
//                insertLocation = parent.row();
//            }
//            else
//            {
//                // else something dropped after the last song, so the songs have to be inserted after the last song
//                insertLocation = playlist->getSongCount() - 1;
//                if (insertLocation < 0)
//                {
//                    insertLocation = 0;
//                }

//            }


//            this->playlist->moveSong(sourceRow, insertLocation);
//            dropped = true;
//        }
    }



QMimeData *SafedPlaylistModel::mimeData(const QModelIndexList &indexes) const
{

    QList<QUrl> filenames;
    QMimeData *mimeData;



    mimeData = QAbstractItemModel::mimeData(indexes);

    qDebug()<<"drag";
    foreach (QModelIndex index, indexes)
    {
    qDebug()<<"index";
        if (index.isValid())
        {
            TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
            if (item->getType() == "PLAYLIST")
            {
               for (int i = 0; i < item->getChilds()->size(); i++)
               {
                   QString filename = item->getChilds()->at(i)->getFilename();
                   QUrl url = QUrl::fromLocalFile(filename);
                   filenames.append(url);
                   qDebug()<<url;

               }

            }
        }

    }

    mimeData->setUrls(filenames);

    return mimeData;
}
