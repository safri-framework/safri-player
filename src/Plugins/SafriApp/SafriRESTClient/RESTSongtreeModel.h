#ifndef RESTSONGTREEMODEL_H
#define RESTSONGTREEMODEL_H

#include <QAbstractItemModel>

namespace Core
{
    class ITreeItem;
}

namespace SafriRESTClient
{
    class RESTSongtreeModel : public QAbstractItemModel
    {
        Q_OBJECT
        public:

            explicit RESTSongtreeModel(Core::ITreeItem *rootItem, QObject *parent = 0);

            // **** BEGIN QAbstractItemModel Interface ****

            QModelIndex index(int row, int column, const QModelIndex &parent) const;
            QModelIndex parent(const QModelIndex &child) const;
            int rowCount(const QModelIndex &parent) const;
            int columnCount(const QModelIndex &parent) const;
            QVariant data(const QModelIndex &index, int role) const;
            QHash<int, QByteArray> roleNames() const;

            // **** END QAbstractItemModel Interface ****


    private:

            enum Roles
            {
                iconRole = Qt::UserRole + 1,
                coverRole = Qt::UserRole + 2,
                typeRole = Qt::UserRole + 3
            };

            Core::ITreeItem* rootItem;
    };
}

#endif // RESTSONGTREEMODEL_H
