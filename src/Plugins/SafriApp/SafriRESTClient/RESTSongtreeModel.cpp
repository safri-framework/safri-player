#include "RESTSongtreeModel.h"
#include "Interfaces/ITreeItem.h"

#include <QDebug>

using namespace SafriRESTClient;

RESTSongtreeModel::RESTSongtreeModel(Core::ITreeItem *rootItem, QObject *parent) :
    QAbstractItemModel(parent), rootItem(rootItem)
{

}


// **** BEGIN QAbstractItemModel Interface Implementation ****

QModelIndex RESTSongtreeModel::index(int row, int column, const QModelIndex &parent) const
{
    Core::ITreeItem* parentItem;

    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<Core::ITreeItem*>(parent.internalPointer());
    }

    Core::ITreeItem* childItem = parentItem->getChildAt(row);

    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex RESTSongtreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
    {
        return QModelIndex();
    }

    Core::ITreeItem *childItem = static_cast<Core::ITreeItem*>(child.internalPointer());
    Core::ITreeItem *parentItem = childItem->getParent();
    int parentIndex;

    if (parentItem == rootItem)
    {
        // the index for the rootItem is an invalid QModelIndex
        return QModelIndex();
    }
    else
    {
        // to create the index for the parent we need the row of it beneath it's own parent item
        parentIndex = parentItem->getParent()->getIndexOfChild(parentItem);
    }

    return createIndex(parentIndex, 0, parentItem);
}

int RESTSongtreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
    {
        // root index
        return rootItem->getChildCount();
    }
    else
    {
        Core::ITreeItem *item = static_cast<Core::ITreeItem*>(parent.internalPointer());

        return item->getChildCount();
    }
}

int RESTSongtreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant RESTSongtreeModel::data(const QModelIndex &index, int role) const
{
    Core::ITreeItem *item = 0;
    item = static_cast<Core::ITreeItem*>(index.internalPointer());

    switch (role)
    {
        case Qt::DisplayRole:
            return item->property("name");
            break;

        case typeRole:
                qDebug()<<item->property("nodeType");
            return item->property("nodeType");
            break;
        default:

            return QVariant();
    }
}

QHash<int, QByteArray> RESTSongtreeModel::roleNames() const
{

    QHash<int, QByteArray> roles;
    roles[iconRole] = "iconpath";
    roles[coverRole] = "albumCover";
    roles[Qt::DisplayRole] ="display";
    roles[typeRole] ="type";

    return roles;
}

// **** END QAbstractItemModel Interface Implementation ****
