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

        SQLStorageAdapter(QUrl filePath);
        ~SQLStorageAdapter();

        virtual Core::ITableModel* loadTable(QString tableName);
        virtual Core::ITableModel* loadTableForDataItemType(Core::DataItem::DATA_ITEM_TYPE type);
        virtual void writeTableForDataItemType(Core::ITableModel* model, Core::DataItem::DATA_ITEM_TYPE type);

        virtual QString getStorageType();
        virtual QUrl getStoragePath();
        virtual QString getContentType();

        //! Specifies the minimum required database version
        static const int DATABASE_VERSION = 3;

    private:

        QUrl sqlFilePath;
        QSqlDatabase database;
        QSqlDatabase& getDatabase();
        QSqlDatabase& getNewDatabase();

        bool createDatabase(QSqlDatabase &db);
        bool checkDatabaseVersion();
        bool checkIfDatabaseExists();
};

#endif // SQLSTORAGEADAPTER_H
