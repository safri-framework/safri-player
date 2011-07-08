#ifndef SONGTREEMODEL_H
#define SONGTREEMODEL_H

#include <QAbstractItemModel>

#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QMimeData>
#include <QIcon>
#include <QImage>

#include "databasedao.h"

/**
    \brief  This class provides a model for a hierarchical tree of BaseDTO objects.

    It builds up a tree structure of BaseDTO objects with the given tree hierarchy
    and provides the interface for it to the view. With this class all database
    objects (i.e. genre, album, artist) can be represented in an arbitrary tree
    structure.
 */
class SongTreeModel : public QAbstractItemModel
{
    Q_OBJECT

    private:

        //! the root of our tree data-structure
        BaseDTO *rootDTO;

        //! this attribute stores the dto object hierarchy of the tree
        QList<BaseDTO::DTO_TYPE> *treeHierarchy;

    public:

        //! Constructs a new SongTreeModel with the specified tree hierarchy of DTO objects
        explicit SongTreeModel(QList<BaseDTO::DTO_TYPE> *sTreeHierarchy, QObject *parent = 0);

        int columnCount(const QModelIndex& parent = QModelIndex()) const;
        int rowCount(const QModelIndex& parent = QModelIndex()) const;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
        QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
        QModelIndex parent(const QModelIndex& index) const;

        Qt::ItemFlags flags(const QModelIndex &index) const;
        QMimeData *mimeData(const QModelIndexList &indexes) const;


};

#endif // SONGTREEMODEL_H
