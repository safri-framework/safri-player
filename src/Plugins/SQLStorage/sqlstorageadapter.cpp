#include "sqlstorageadapter.h"
#include "icore.h"
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include "CoreData/dataitemtablemodel.h"

SQLStorageAdapter::SQLStorageAdapter(QUrl filePath)
    : sqlFilePath(filePath)
{
}

SQLStorageAdapter::~SQLStorageAdapter()
{
}

Core::ITableModel *SQLStorageAdapter::loadTable(QString tableName)
{
    if ( !checkIfDatabaseExists() )
    {
        qDebug() << "Database doesn't exist";
        return 0;
    }

    if ( !checkDatabaseVersion() )
    {
        qDebug() << "Database version mismatch";
        return 0;
    }

    QString queryStmt = "SELECT COUNT(*) FROM " + tableName;
    int querySize, recordSize;

    qDebug() << queryStmt;

    QSqlQuery query( getDatabase() );


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

void SQLStorageAdapter::writeTableForDataItemType(Core::ITableModel *model, Core::DataItem::DATA_ITEM_TYPE type)
{
}

QString SQLStorageAdapter::getStorageType()
{
    return STORAGE_TYPE;
}

QSqlDatabase &SQLStorageAdapter::getDatabase()
{
    if ( !database.open() )
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "safri");
        database.setDatabaseName(Core::ICore::storageDirectory() + "sqlitedatabasev2.db");
    }

    if( !database.open() )
    {
        qDebug() << database.lastError();
        qFatal("Failed to connect to database.");
    }

    return database;
}

QSqlDatabase &SQLStorageAdapter::getNewDatabase()
{
    database.close();

    QDir dir(Core::ICore::storageDirectory());

    dir.remove("sqlitedatabasev2_old.db");
    dir.rename("sqlitedatabasev2.db", "sqlitedatabasev2_old.db");

    if( !database.open() )
    {
        qDebug() << database.lastError();
        qFatal("Failed to connect to database.");
    }

    return database;
}

bool SQLStorageAdapter::createDatabase(QSqlDatabase &db)
{
    qDebug()<<db.open();

    QSqlQuery query( db );

    QString createAlbum = "CREATE TABLE Album \
            ( \
                    id INTEGER PRIMARY KEY, \
                    album VARCHAR(300), \
                    year INTEGER, \
                    album_cover TEXT,  \
                    number_of_cds INTEGER,  \
                    number_of_tracks INTEGER, \
                    is_complete BOOLEAN,  \
                    info VARCHAR(1000),  \
                    is_live BOOLEAN \
            );";
    QString createArtist = "CREATE TABLE Artist \
            ( \
                    id	INTEGER NOT NULL CONSTRAINT pk_artist_id PRIMARY KEY, \
                    artist	VARCHAR(300) NOT NULL, \
                    info	VARCHAR(1000), \
                    entire_discography BOOLEAN, \
                    rating INTEGER \
            );";
    QString insertArtist = "INSERT INTO Artist VALUES(-1,'Unbekannt',NULL,NULL,NULL);";

    QString createArtistToAlbum = "CREATE TABLE ArtistToAlbum (artist_id NUMERIC, album_id NUMERIC);";
    QString createCD = "CREATE TABLE CD \
                        ( \
                                id	INTEGER NOT NULL CONSTRAINT pk_cd_id PRIMARY KEY, \
                                album_id INTEGER CONSTRAINT fk_cd_album_id REFERENCES Album(id), \
                                number	INTEGER NOT NULL, \
                                number_of_tracks INTEGER \
                        );";
    QString createDatabaseInfo = "CREATE TABLE DATABASE_INFO (DATABASE_VERSION NUMERIC);";
    QString insertVersion = "INSERT INTO DATABASE_INFO VALUES(3);";
    QString createGenre = "CREATE TABLE Genre \
            ( \
                    id	INTEGER NOT NULL CONSTRAINT pk_genre_id PRIMARY KEY, \
                    genre	VARCHAR(50) NOT NULL UNIQUE \
            );";
    QString createSong = "CREATE TABLE Song \
            ( \
                id INTEGER PRIMARY KEY, \
                song VARCHAR(305), \
                artist_id INTEGER, \
                genre_id INTEGER, \
                album_id INTEGER, \
                cd_id INTEGER, \
                year INTEGER, \
                info VARCHAR(1000), \
                songtext VARCHAR(10000), \
                track_number INTEGER, \
                length INTEGER, \
                filename VARCHAR(1000), \
                rating INTEGER, \
                comment VARCHAR(1000) \
            );";
    QString createTag = "CREATE TABLE Tag \
            ( \
                    id	INTEGER NOT NULL CONSTRAINT pk_tag_id PRIMARY KEY, \
                    tag	VARCHAR(140) NOT NULL UNIQUE \
            );";

    QStringList statements;
    statements << createAlbum << createArtist << insertArtist << createArtistToAlbum << createCD << createDatabaseInfo \
               << insertVersion << createGenre << createSong << createTag;

    qDebug() << "Creating database...";

    for (int i = 0; i < statements.size(); i++)
    {
        if ( !query.exec(statements.at(i)))
        {
            qDebug() << "ERROR: " << statements.at(i) << query.lastError();
            return false;
        }
    }

    return true;
}

bool SQLStorageAdapter::checkDatabaseVersion()
{
    QSqlQuery query( getDatabase() );
    QString queryStmt = "SELECT DATABASE_VERSION FROM DATABASE_INFO";

    if ( !query.exec(queryStmt))
    {
        qDebug() << "ERROR: " << queryStmt << query.lastError();
        return false;
    }

    query.next();

    int databaseVersion = query.value( query.record().indexOf("DATABASE_VERSION") ).toInt();

    return databaseVersion >= DATABASE_VERSION;
}

bool SQLStorageAdapter::checkIfDatabaseExists()
{
    QSqlQuery query( getDatabase() );
    QString queryStmt = "SELECT COUNT(type) FROM sqlite_master WHERE type='table' AND name='Artist';";

    if ( !query.exec(queryStmt))
    {
        qDebug() << "ERROR: " << queryStmt << query.lastError();
        return false;
    }

    query.next();

    int tableCount = query.value(0).toInt();

    return tableCount > 0;
}

QUrl SQLStorageAdapter::getStoragePath()
{
    return QUrl();
}

QString SQLStorageAdapter::getContentType()
{
    return "org.safri.collection.audio";
}
