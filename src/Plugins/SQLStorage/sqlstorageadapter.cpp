#include "sqlstorageadapter.h"
#include "icore.h"
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include "CoreData/dataitemtablemodel.h"

SQLStorageAdapter::SQLStorageAdapter(QUrl filePath, QObject *parent)
    : IStorageAdapter(parent), sqlFilePath(filePath), currentTransaction(TA_NONE)
{

}

SQLStorageAdapter::~SQLStorageAdapter()
{
}

Core::ITableModel *SQLStorageAdapter::loadTable(QString tableName)
{
    QString queryStmt = "SELECT COUNT(*) FROM " + tableName;
    int querySize, recordSize;

    qDebug() << queryStmt;

    if (!database.open())
    {
        return 0;
    }

    QSqlQuery query( database );


    if ( !query.exec(queryStmt))
    {
        qDebug() << "ERROR: " << queryStmt << query.lastError();
        return 0;
    }

    query.next();
    querySize = query.value(0).toInt();

    queryStmt = "SELECT * FROM " + tableName;
    if ( !query.exec(queryStmt))
    {
        qDebug() << "ERROR: " << queryStmt << query.lastError();
        return 0;
    }

    if (!query.next() )
    {
        return 0;
    }

    recordSize = query.record().count();

    Core::DataItemTableModel* tableModel = new Core::DataItemTableModel(querySize, recordSize);

    for (int c = 0; c < recordSize; c++)
    {
        tableModel->setHeaderData(c, Qt::Horizontal, query.record().fieldName(c));
    }

    int row = 0;
    do
    {
        for (int c = 0; c < recordSize; c++)
        {
            tableModel->setData(tableModel->index(row, c), query.value(c));
        }
        row++;
    }
    while (query.next());


    return tableModel;
}

Core::ITableModel *SQLStorageAdapter::loadTableForDataItemType(Core::DataItem::DATA_ITEM_TYPE type)
{
    return loadTable(Core::DataItem::typeToString(type));
}

bool SQLStorageAdapter::beginWrite()
{

    if (currentTransaction != TA_NONE)
    {
        qDebug() << "Can't begin write: Current database transaction running!";
        return false;
    }

    currentTransaction = TA_WRITE;
    database.close();

    QString tempFilePath = sqlFilePath.toString().append(".tmp");

    QDir dir(sqlFilePath.path());
    dir.remove(tempFilePath);   // remove any existent temporary database

    qDebug() << "removed old temp file";

    database.setDatabaseName(tempFilePath);

    if( !database.open() )
    {
        qDebug() << "Database error:";
        qDebug() << database.lastError().driverText();
        qFatal("Failed to connect to database.");

        database.setDatabaseName(sqlFilePath.toString());
        currentTransaction = TA_NONE;

        return false;
    }

    if ( !createDatabase() )
    {
        qDebug() << "Database error:";
        qDebug() << database.lastError().driverText();
        qFatal("Could not create database structure");

        database.setDatabaseName(sqlFilePath.toString());
        dir.remove(tempFilePath);

        currentTransaction = TA_NONE;

        return false;
    }

    QSqlQuery query(database);
    if ( !query.exec("BEGIN") )
    {
       qDebug() << "ERROR: " << "BEGIN" << query.lastError();
       return false;
    }


    return true;
}

bool SQLStorageAdapter::endWrite()
{
    if (currentTransaction == TA_WRITE)
    {

        QSqlQuery query(database);
        if ( !query.exec("COMMIT") )
        {
           qDebug() << "ERROR: " << "COMMIT" << query.lastError();
           return false;
        }

        database.close();
        QString filePath = sqlFilePath.toString();
        QDir dir(sqlFilePath.path());

        dir.remove(filePath);
        dir.rename(filePath + ".tmp", filePath);

        currentTransaction = TA_NONE;
        return true;
    }

    return false;
}

bool SQLStorageAdapter::abortWrite()
{
    if (currentTransaction == TA_WRITE)
    {
        QString tempFilePath = sqlFilePath.toString().append(".tmp");

        QDir dir(sqlFilePath.path());
        dir.remove(tempFilePath);
        database.setDatabaseName(sqlFilePath.toString());

        currentTransaction = TA_NONE;

        return true;
    }

    return false;
}

bool SQLStorageAdapter::beginRead()
{
    if (currentTransaction != TA_NONE)
    {
        qDebug() << "Can't begin read: Current database transaction running!";
        return false;
    }

    qDebug() << "Databasefile:"  << sqlFilePath.toString();

    if ( !database.open() )
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "safri");
        database.setDatabaseName(sqlFilePath.toString());
    }

    if( !database.open() )
    {
        qDebug() << "Database error:";
        qDebug() << database.lastError().driverText();
        qFatal("Failed to connect to database.");
        return false;
    }

    if ( !checkIfDatabaseExists() )
    {
        qDebug() << "Database doesn't exist";
        createDatabase();
        return false;
    }

    if ( !checkDatabaseVersion() )
    {
        qDebug() << "Database version mismatch";
        return false;
    }

    currentTransaction = TA_READ;

    return true;
}

bool SQLStorageAdapter::endRead()
{
    database.close();
    currentTransaction = TA_NONE;
    return true;
}

QUrl SQLStorageAdapter::getStoragePath()
{
    return sqlFilePath;
}

QString SQLStorageAdapter::getCollectionType()
{
    return AUDIO_COLLECTION_TYPE;
}

QString SQLStorageAdapter::getStorageType()
{
    return STORAGE_TYPE;
}

