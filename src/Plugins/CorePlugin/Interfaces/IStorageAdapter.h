#ifndef ISTORAGEADAPTER_H
#define ISTORAGEADAPTER_H

#include "../CorePlugin_global.h"
#include "../CoreData/dataitem.h"
#include "ITableModel.h"
#include <QUrl>
#include <QString>

namespace Core
{
    class COREPLUGINSHARED_EXPORT IStorageAdapter : public QObject
    {
        Q_OBJECT
        public:

            IStorageAdapter(QObject *parent);
            virtual ~IStorageAdapter();

            virtual ITableModel* loadTable(QString table) = 0;
            virtual ITableModel* loadTableForDataItemType(DataItem::DATA_ITEM_TYPE type) = 0;
            virtual bool writeTable(ITableModel* model, QString table) = 0;
            virtual bool writeTableForDataItemType(ITableModel* model, DataItem::DATA_ITEM_TYPE type) = 0;

            virtual QString getStorageType() = 0;

            /**
                \brief  This function starts a write transaction.

                        Implement this function to start a write transaction eg. open
                        a database connection, create a temporary database, create the
                        data structure, etc.

                \returns success of operation
            */
            virtual bool beginWrite() = 0;

            /**
                \brief  This function ends a write transaction.

                        Implement this function to finish a write transaction eg. close
                        the database connection, rename temporary databse, etc.

                \returns success of operation
            */
            virtual bool endWrite() = 0;

            /**
                \brief  This function aborts a write transaction.

                        Implement this function to abort a write transaction eg. close
                        the database connection, remove temporary databse, etc.

                \returns success of operation
            */
            virtual bool abortWrite() = 0;

            /**
                \brief  This function starts a read transaction.

                        Implement this function to start a read transaction eg. open
                        a database connection, check database version, etc.

                \returns success of operation
            */
            virtual bool beginRead() = 0;

            /**
                \brief  This function ends a read transaction.

                        Implement this function to end a read transaction eg. close
                        a database connection, etc.

                \returns success of operation
            */
            virtual bool endRead() = 0;

            // Database location!
            virtual QUrl getStoragePath() = 0;
            virtual QString getCollectionType() = 0;

    };
}

Q_DECLARE_INTERFACE(Core::IStorageAdapter, "Core::IStorageAdapter")

#endif // ISTORAGEADAPTER_H
