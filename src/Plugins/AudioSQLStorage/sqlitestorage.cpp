#include "sqlitestorage.h"
#include <QDebug>
#include <QSqlError>
#include <QDir>

SQLiteStorage::SQLiteStorage(QUrl url, QObject *parent) :
    ISQLStorage(parent), url(url), currentMode(INVALID)
{
    database = QSqlDatabase::addDatabase( "QSQLITE", url.toString() );
}

SQLiteStorage::~SQLiteStorage()
{
    qDebug() << "~SQLiteStorage()";
    close();
    QSqlDatabase::removeDatabase( url.toString() );
}

bool SQLiteStorage::open(ISQLStorage::OPERATION_MODE openMode)
{
    if (currentMode != INVALID)
    {
        qDebug() << "Error: Database already open!";
        return false;
    }

    if (openMode == READ)
    {
        qDebug() << "Databasefile:"  << url.toString();

        // for android the path for the databasefile must exist before
        // the file can be created
        QString databasePath = QFileInfo(url.toString()).absolutePath();
        QDir dir(databasePath);
        if(!dir.exists())
        {
            dir.mkpath(databasePath);
        }

        database.setDatabaseName(url.toString());

        if( !database.open() )
        {
            qDebug() << "Database error:";
            qDebug() << database.lastError().driverText();
            qFatal("Failed to connect to database.");
            return false;
        }

        currentMode = openMode;
        return true;
    }
    else if (openMode == WRITE)
    {
        qDebug() << "Open database for read";
        QString tempFilePath = url.toString().append(".tmp");

        QDir dir(url.path());
        dir.remove(tempFilePath);   // remove any existent temporary database

        database.setDatabaseName(tempFilePath);

        if( !database.open() )
        {
            qDebug() << "Database error:";
            qDebug() << database.lastError().driverText();

            database.setDatabaseName(url.toString());
            currentMode = INVALID;

            return false;
        }

        currentMode = openMode;
        return true;
    }

    return false;
}

bool SQLiteStorage::close()
{
    qDebug() << "SQLiteStorage::close()";

    if (currentMode == READ)
    {
        qDebug() << "Database READ -> CLOSE";
        database.close();
        currentMode = INVALID;
        return true;
    }
    else if (currentMode == WRITE)
    {
        qDebug() << "Database WRITE -> CLOSE";
        currentMode = INVALID;

        database.close();
        QString filePath = url.toString();
        QDir dir(url.path());

        dir.remove(filePath);
        dir.rename(filePath + ".tmp", filePath);

        return true;
    }

    return false;
}

bool SQLiteStorage::abort()
{
    if (currentMode == READ)
    {
        database.close();
        currentMode = INVALID;
        return true;
    }
    else if (currentMode == WRITE)
    {
        currentMode = INVALID;
        database.close();
        QString filePath = url.toString();
        QDir dir(url.path());

        dir.remove(filePath + ".tmp");

        return true;
    }

    return false;
}

QSqlQuery SQLiteStorage::createQuery()
{
    return QSqlQuery(database);
}
