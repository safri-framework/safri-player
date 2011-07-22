#include "datatablemodel.h"

#include <QMimeData>
#include <QIcon>
#include <QUrl>

DataTableModel::DataTableModel(DatabaseDAO::DataTable* dataTable, QObject *parent) :
    QAbstractTableModel(parent), dataTable(dataTable)
{

}


int DataTableModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return dataTable->length();
    else
        return 0;
}


int DataTableModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 4;
    else
        return 0;
}

QVariant DataTableModel::data(const QModelIndex &index, int role) const
{
    if ( index.isValid() )
    {
        switch (role)
        {
            case Qt::DisplayRole:

                switch ( index.column() )
                {
                    case 0:

                        return dataTable->at(index.row())->value("ARTIST");
                        break;

                    case 1:

                        return dataTable->at(index.row())->value("SONG");
                        break;

                    case 2:

                        return dataTable->at(index.row())->value("ALBUM");
                        break;

                    case 3:

                        return dataTable->at(index.row())->value("GENRE");
                        break;
                }
                break;

            case Qt::DecorationRole:

                if ( index.column() == 0)
                    return QIcon("img/song_icon.png");
                break;

            default:

                return QVariant();
        }

    }
    else
        return QVariant();

    return QVariant();

}

QMimeData *DataTableModel::mimeData(const QModelIndexList &indexes) const
{
    QList<QUrl> filenames;
    QMimeData *mimeData = new QMimeData();


    foreach (QModelIndex index, indexes)
    {
        if (index.isValid() && index.column() == 0)
        {         
            filenames.append(QUrl::fromLocalFile(dataTable->at(index.row())->value("FILENAME")));
        }

    }

    mimeData->setUrls(filenames);

    return mimeData;
}

QVariant DataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole )
    {

        switch (section)
        {

            case 0:
                return "Interpret";

            case 1:
                return "Titel";

            case 2:
                return "Album";

            case 3:
                return "Genre";

        }
    }

    return QVariant();
}

Qt::ItemFlags DataTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if ( index.isValid())
    {
        return Qt::ItemIsDragEnabled | defaultFlags;
    }
    else
    {
        return defaultFlags;
    }
}

