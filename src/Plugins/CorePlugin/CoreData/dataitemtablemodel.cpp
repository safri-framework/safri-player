#include "dataitemtablemodel.h"
#include <QVariant>
#include <QDebug>

using namespace Core;

DataItemTableModel::DataItemTableModel(int rows, int columns, QObject* parent)
    : QAbstractTableModel(parent), dataSource(Table(rows, TableRow(columns))), columnHeaders(TableRow(columns))
{
}

Core::DataItemTableModel::~DataItemTableModel()
{

}

int DataItemTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    else
    {
        return dataSource.size();
    }
}

int DataItemTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    else
    {
        if (dataSource.size() > 0)
        {
            return dataSource[0].size();
        }
    }

    return 0;
}

QVariant DataItemTableModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        if (role == Qt::DisplayRole)
        {
            return dataSource[index.row()][index.column()];
        }
    }

    return QVariant();
}

Qt::ItemFlags DataItemTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
    return Qt::ItemIsEditable | defaultFlags;
}

bool DataItemTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::DisplayRole)
    {
        dataSource[index.row()][index.column()] = value.toString();
        Q_EMIT dataChanged(index, index);
        return true;
    }

    return false;
}

QVariant DataItemTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return columnHeaders[section];
    }
}
