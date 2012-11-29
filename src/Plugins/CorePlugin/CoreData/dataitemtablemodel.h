#ifndef DATAITEMTABLEMODEL_H
#define DATAITEMTABLEMODEL_H

#include "../CorePlugin_global.h"
#include "../Interfaces/ITableModel.h"
#include <QVector>

namespace Core
{
    class COREPLUGINSHARED_EXPORT DataItemTableModel : public ITableModel
    {
        public:

            DataItemTableModel(int rows, int columns, QObject* parent = 0);
            virtual ~DataItemTableModel();

            int rowCount(const QModelIndex &parent) const;
            int columnCount(const QModelIndex &parent) const;
            QVariant data(const QModelIndex &index, int role) const;

            Qt::ItemFlags flags(const QModelIndex &index) const;
            bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);

            QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
            bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::DisplayRole);

            int indexOfColumn(QString column);

        private:

            typedef QVector<QString> TableRow;
            typedef QVector<TableRow> Table;

            Table dataSource;
            TableRow columnHeaders;
    };
}

#endif // DATAITEMTABLEMODEL_H
