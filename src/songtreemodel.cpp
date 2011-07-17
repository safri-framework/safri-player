#include "songtreemodel.h"
#include <QDirIterator>


SongTreeModel::SongTreeModel(QList<BaseDTO::DTO_TYPE> *sTreeHierarchy, QObject *parent) :
            QAbstractItemModel(parent), treeHierarchy(sTreeHierarchy)
{


    rootDTO = new BaseDTO(0, "", treeHierarchy->at(0));

    //DatabaseDAO::fillDTO(rootDTO, treeHierarchy);

    DatabaseDAO::LoadSongTree(rootDTO, treeHierarchy);

    // preload data for second tree level
    /*
    if (rootDTO->getChildren() != 0)
    {
        int size = rootDTO->getChildren()->size();

        for (int i = 0; i < size; i++)
        {
            DatabaseDAO::fillDTO(rootDTO->getChildren()->at(i), treeHierarchy);
        }

    }
    */

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

        // For all DTOs which will be stored in a ModelIndex, we load
        // it's children so i.e. the rowCount for this index is determined
        //DatabaseDAO::fillDTO(dtoForIndex, treeHierarchy);

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
        return Qt::ItemIsDragEnabled | defaultFlags;
    }
    else
    {
        return defaultFlags;
    }
}

QMimeData *SongTreeModel::mimeData(const QModelIndexList &indexes) const
{
    QList<QUrl> filenames;
    QMimeData *mimeData = new QMimeData();


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



void SongTreeModel::dragEnterEvent(QDragEnterEvent *event)
 {

    event->acceptProposedAction();

 }



void SongTreeModel::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {

        QList<QUrl> urllist = mimeData->urls();
        QStringList* files = new QStringList();


        foreach (QUrl i, urllist)
        {

            if (QFileInfo(i.toLocalFile()).suffix() == "mp3" || QFileInfo(i.toLocalFile()).suffix() == "ogg" )
            {

                files->append(QFileInfo(i.toLocalFile()).absoluteFilePath());

            }

            else if(QFileInfo(i.toLocalFile()).isDir())
            {


                if (!i.isEmpty())
                {

                    QDir dir(i.toLocalFile());
                    QStringList filters;
                    filters << "*.mp3" << "*.wma" << "*.ogg";
                    dir.setNameFilters(filters);

                    QDirIterator lukeFileWalker(dir, QDirIterator::Subdirectories);


                    while (lukeFileWalker.hasNext())
                    {
                        lukeFileWalker.next();
                        files->append(lukeFileWalker.fileInfo().absoluteFilePath());
                    }



                }
                if (!files->isEmpty())
                {
                qDebug()<<"einügen";
                }
            }

        }
    }
}
