#ifndef DATATABLEMODEL_H
#define DATATABLEMODEL_H

#include <QAbstractTableModel>
#include "databasedao.h"

class QMimeData;

class DataTableModel : public QAbstractTableModel
{
    Q_OBJECT
    public:
        explicit DataTableModel(DatabaseDAO::DataTable* dataTable, QObject *parent = 0);
        virtual int rowCount(const QModelIndex &parent) const;
        virtual int columnCount(const QModelIndex &parent) const;

        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        QMimeData *mimeData(const QModelIndexList &indexes) const;

        QVariant headerData(int section, Qt::Orientation orientation, int role) const;

        Qt::ItemFlags flags(const QModelIndex &index) const;
    signals:

    public slots:

    private:

        DatabaseDAO::DataTable* dataTable;

};

#endif // DATATABLEMODEL_H
