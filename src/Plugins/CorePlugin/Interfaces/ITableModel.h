#ifndef ITABLEMODEL_H
#define ITABLEMODEL_H

#include "../CorePlugin_global.h"
#include <QAbstractTableModel>

namespace Core
{
    class COREPLUGINSHARED_EXPORT ITableModel : public QAbstractTableModel
    {
        public:

            ITableModel(QObject* parent);
            virtual ~ITableModel();
            virtual int indexOfColumn(QString column) = 0;
    };
}

#endif // ITABLEMODEL_H
