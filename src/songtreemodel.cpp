#include "songtreemodel.h"
#include <QDirIterator>
#include <playerwidget.h>


SongTreeModel::SongTreeModel(QList<BaseDTO::DTO_TYPE> *sTreeHierarchy, DatabaseDAO::DataTable* useDataTable, QObject *parent) :
            QAbstractItemModel(parent), treeHierarchy(sTreeHierarchy)
{
    rootDTO = DatabaseDAO::BuildSongTree(treeHierarchy, useDataTable);
}


int SongTreeModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

int SongTreeModel::rowCount(const QModelIndex& parent) const
{
    if ( parent.isValid() )
    {
        // valid ModelIndexes stores the pointer to its corresponding BaseDTO object
        // so we can directly get the BaseDTO object and return the number of its children (rows)
        BaseDTO *dto = static_cast<BaseDTO*>(parent.internalPointer());

        if (dto->getChildren() == 0)
        {
            return 0;
        }
        else
        {
            return dto->getChildren()->length();
        }

    }
    else
    {
        // for the invalid root ModelIndex return the number of children
        // from the rootDTO object

        if (rootDTO->getChildren() != 0)
        {
            return rootDTO->getChildren()->length();
        }
        else
        {
            return 0;
        }

    }

}

QVariant SongTreeModel::data(const QModelIndex& index, int role) const
{

    if ( index.isValid() )
    {
        // as valid ModelIndexes stores the pointer to its represented BaseDTO object
        // the data can directly accessed by the ModelIndex' internal pointer
        BaseDTO *dto = static_cast<BaseDTO*>(index.internalPointer());;

        if (dto == 0)
        {
            return QVariant();
        }

        switch (role)
        {
            case Qt::DisplayRole:

                return dto->getText();

            case Qt::DecorationRole:


                if (dto->getType() == BaseDTO::SONG)
                {
                    return QIcon("img/song_icon.png");
                }
                else
                {
                    if (dto->getType() == BaseDTO::ALBUM)
                    {
                        //return QIcon(DatabaseDAO::getAlbumCover(dto->getID()));

                        QImage image("covers\\" + QString::number(dto->getID()) + ".jpg");

                        if ( image.isNull() )
                        {
                            image.load("covers\\default.png");
                        }


                        return image;
                    }

                    return QIcon("img/music_icon.png");
                }


            default:

                return QVariant();
        }

    }
    else
    {
        return QVariant();
    }


}

QModelIndex SongTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    BaseDTO *parentDTO = 0;

    // as we want to create a ModelIndex below the parent Index
    // first we choose the right parent DTO object
    if ( parent.isValid() )
    {
        parentDTO = static_cast<BaseDTO*>(parent.internalPointer());
    }
    else
    {
        parentDTO = rootDTO;
    }

    if (parentDTO != 0 && parentDTO->getChildren() != 0 && parentDTO->getChildren()->length() > 0)
    {
        // the DTO which the new ModelIndex will represent ist the children
        // from the parentDTO at the requested row
        BaseDTO *dtoForIndex = parentDTO->getChildren()->at(row);

        return createIndex(row, column, dtoForIndex);
    }
    else
    {
        return QModelIndex();
    }

}

QModelIndex SongTreeModel::parent(const QModelIndex& index) const
{
    if ( index.isValid() )
    {
        BaseDTO *dto = static_cast<BaseDTO*>(index.internalPointer());
         int row;

        if (dto->getParentDTO() == 0 || dto->getParentDTO() == rootDTO)
        {
            return QModelIndex();
        }
        else
        {
            if (dto->getParentDTO()->getParentDTO() == 0)
            {
               row = rootDTO->getChildren()->indexOf( dto->getParentDTO() );

            }
            else
            {
               row = dto->getParentDTO()->getParentDTO()->getChildren()->indexOf( dto->getParentDTO() );
            }
        }


        return createIndex(row, 0, dto->getParentDTO());


    }
    else
    {
        return QModelIndex();
    }
}

Qt::ItemFlags SongTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
    {
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    }
    else
    {
        return Qt::ItemIsDropEnabled | defaultFlags;
    }
}

QMimeData *SongTreeModel::mimeData(const QModelIndexList &indexes) const
{
    QList<QUrl> filenames;
    QMimeData *mimeData = new QMimeData();
    mimeData->setText("SongTreeMimeData");

    foreach (QModelIndex index, indexes)
    {
        if (index.isValid())
        {
            BaseDTO *dto = static_cast<BaseDTO*>(index.internalPointer());
            filenames.append(DatabaseDAO::getUrlsByBaseDTO(dto));
        }

    }

    mimeData->setUrls(filenames);

    return mimeData;
}


QStringList SongTreeModel::mimeTypes() const
{
    QStringList types = QAbstractItemModel::mimeTypes();
    types << "text/uri-list";

    return types;
}




Qt::DropActions SongTreeModel::supportedDropActions() const
{
    return Qt::CopyAction ;
}



bool SongTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    bool dropped = false;
        if (data->hasFormat("text/uri-list") && data->text()!="SongTreeMimeData")
        {

            QList<QUrl> urls = data->urls();
            QStringList* filenames = new QStringList();




            foreach (QUrl i, urls)
            {

                QString suffix = "*."+QFileInfo(i.toLocalFile()).suffix();
                if (PlayerWidget::getSupportedFileTypes()->contains(suffix))
                {
                    filenames->append(i.toLocalFile());


                }

                else
                {


                    if (!i.isEmpty())
                    {

                        QDir dir(i.toLocalFile());
                        QStringList filters = *PlayerWidget::getSupportedFileTypes();
                        filters << "*.mp3" << "*.wma" << "*.ogg";
                        dir.setNameFilters(filters);

                        QDirIterator lukeFileWalker(dir, QDirIterator::Subdirectories);


                        while (lukeFileWalker.hasNext())
                        {
                            lukeFileWalker.next();
                            filenames->append(lukeFileWalker.fileInfo().absoluteFilePath());

                        }


                    }
                }

            }



            if (filenames->size() > 0)
            {

                Q_EMIT songsToInsertInDatabase(filenames);

            }

            dropped = true;


        }
    }

