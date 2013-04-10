#ifndef SQLSTORAGEADAPTER_H
#define SQLSTORAGEADAPTER_H

#include "SQLStorage_global.h"
#include "Interfaces/IStorageAdapter.h"
#include "CoreData/dataitemtablemodel.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class SQLSTORAGESHARED_EXPORT SQLStorageAdapter : public Core::IStorageAdapter
{
    public:

        SQLStorageAdapter(QUrl filePath, QObject *parent);
        ~SQLStorageAdapter();

        virtual Core::ITableModel* loadTable(QString tableName);
        virtual Core::ITableModel* loadTableForDataItemType(Core::DataItem::DATA_ITEM_TYPE type);

        virtual bool beginWrite();
        virtual bool endWrite();
        virtual bool abortWrite();
        virtual bool beginRead();
        virtual bool endRead();

        virtual QString getStorageType();
        virtual QUrl getStoragePath();
        virtual QString getCollectionType();

        //! Specifies the minimum required database version
        static const int DATABASE_VERSION = 3;

    protected:

        QUrl sqlFilePath;
        QSqlDatabase database;

        enum TRANSACTION_TYPE { TA_NONE, TA_READ, TA_WRITE };

        TRANSACTION_TYPE currentTransaction;

        virtual bool createDatabase() = 0;
        virtual bool checkDatabaseVersion() = 0;
        virtual bool checkIfDatabaseExists() = 0;
};

#endif // SQLSTORAGEADAPTER_H
