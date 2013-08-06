#ifndef SONGTREEMODEL_H
#define SONGTREEMODEL_H

#include <QAbstractItemModel>
#include <QMimeData>
#include <QMap>
#include <QStringList>

#include "../CorePlugin_global.h"
#include "songtree.h"
#include "songtreeitem.h"
#include "Interfaces/ISafriSkin.h"

/**
    \brief model for the song tree
*/
using namespace Core;

class COREPLUGINSHARED_EXPORT SongTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    public:

        explicit SongTreeModel(SongTree* songTree, QObject *parent = 0);

    public:

        /**
            \param      the parent QModelIndex
            \returns    the column count for the parent QModelIndex
        */
        int columnCount(const QModelIndex &parent = QModelIndex()) const;

        /**
            \param      the parent QModelIndex
            \returns    the row count for the parent QModelIndex
        */
        int rowCount(const QModelIndex &parent = QModelIndex()) const;

        /**
            \param      the QModelIndex
            \returns    the parent QModelIndex for the index
        */
        QModelIndex parent(const QModelIndex &index) const;

        /**
            Accessor for the data of a QModelIndex

            \param      the QModelIndex
            \param      the data role
            \returns    the data for the QModelIndex with the specified role
        */
        QVariant data(const QModelIndex &index, int role) const;

        /**
            Creates a QModelIndex for the specified parameters

            \param      the row of the new QModelIndex within its parent
            \param      the column of the new QModelIndex
            \param      the parent QModelIndex
            \returns    the new QModelIndex
        */
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

        virtual QHash<int, QByteArray> roleNames() const;



        QVariant headerData(int section, Qt::Orientation orientation, int role) const;




    public slots:

        /**
          Inserts a new item into the given position.

          \param        the parent SongTreeItem
          \param        the row of the new inserted child
        */
        void insertItem(SongTreeItem* parent, int row);

        /**
          Removes an item from the given position.

          \param        the parent SongTreeItem
          \param        the row of the removed child
        */
        void removeItem(SongTreeItem* parent, int row);

        /**
          Receives the dropped Data.

          \param        the MimeData object
          \param        the DropAction (copy / move)
          \param        the row number
          \param        the column number
          \param        the Model Index where the data was dropped

        */
        virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
        virtual Qt::DropActions supportedDropActions() const;
        virtual Qt::DropActions supportedDragActions() const;
        Qt::ItemFlags flags(const QModelIndex &index) const;


        /**
          Builds the MimeData Object from drag operations

          \param        the selected MoedelIndexes


        */
        QMimeData *mimeData(const QModelIndexList &indexes) const;



        QStringList mimeTypes() const;


        void beginMoveItem(SongTreeItem *srcParent, int srcRow, SongTreeItem *destParent, int destRow);
        void endMoveItem(SongTreeItem *destParent);
        void beginInsertItem(SongTreeItem *parent, int row);
        void endInsertItem();
        void beginRemoveItem(SongTreeItem *parent, int row);
        void endRemoveItem();

        Q_INVOKABLE QModelIndex artistIndex(int row);

private:
        enum Roles
        {
            iconRole = Qt::UserRole + 1,
            coverRole = Qt::UserRole + 2,
            typeRole = Qt::UserRole + 3
        };
        SongTree* songTree;
        QMap<SongTreeItem*, QModelIndex> indexMap;

        QModelIndex getModelIndexForItem(SongTreeItem* item);
        ISafriSkin* skin;

signals:

        void songAttributesChanged(Item* song, QString artist, QString album, QString genre);
        void dragAndDropOperation(QList<SongTreeItem*> source, QList<SongTreeItem*> oldParents, SongTreeItem* target);
        void dropOperationOccured();
};

#endif // SONGTREEMODEL_H
