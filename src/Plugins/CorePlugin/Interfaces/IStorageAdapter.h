#ifndef ISTORAGEADAPTER_H
#define ISTORAGEADAPTER_H

#include "../CorePlugin_global.h"
#include "../CoreData/dataitem.h"
#include <QAbstractTableModel>
#include <QUrl>
#include <QString>

namespace Core
{
    class COREPLUGINSHARED_EXPORT IStorageAdapter
    {
        public:

            virtual ~IStorageAdapter();

            virtual QAbstractTableModel* loadTableForDataItemType(DataItem::DATA_ITEM_TYPE type) = 0;
            virtual void writeTableForDataItemType(QAbstractTableModel* model, DataItem::DATA_ITEM_TYPE type) = 0;

            virtual QString getStorageType() = 0;
            virtual QUrl getStoragePath() = 0;
    };
}

#endif // ISTORAGEADAPTER_H
