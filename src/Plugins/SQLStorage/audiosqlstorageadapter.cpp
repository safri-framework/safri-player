#include "audiosqlstorageadapter.h"
#include <QDebug>
#include <QStringList>

AudioSQLStorageAdapter::AudioSQLStorageAdapter(QUrl filePath, QObject *parent) :
    SQLStorageAdapter(filePath, parent)
{
    /*
    if (!beginRead())
    {
        qDebug() << "Database error";
    }
    */
}

bool AudioSQLStorageAdapter::createDatabase()
{
    qDebug()<<database.open();


    if (!database.open())
    {
        return false;
    }

    QSqlQuery query( database );

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

bool AudioSQLStorageAdapter::checkDatabaseVersion()
{
    if (!database.open())
    {
        return false;
    }

    QSqlQuery query( database );
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

bool AudioSQLStorageAdapter::checkIfDatabaseExists()
{
    if (!database.open())
    {
        return false;
    }

    QSqlQuery query( database );
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

bool AudioSQLStorageAdapter::writeGenreTable(Core::ITableModel *model)
{
    QString insertStatement = "INSERT INTO genre VALUES (?, ?)";
    QSqlQuery query(database);

    int genreCount = model->rowCount();
    int idIndex = model->indexOfColumn("id");
    int nameIndex = model->indexOfColumn("genre");

    for (int i = 0; i < genreCount; i++)
    {
        query.prepare(insertStatement);
        query.bindValue(0, model->data(model->index(i, idIndex)).toInt());
        query.bindValue(1, model->data(model->index(i, nameIndex)).toString());

        if ( !query.exec() )
        {
            qDebug() << "ERROR: " << insertStatement << query.lastError();
            return false;
        }
    }

    return true;
}

bool AudioSQLStorageAdapter::writeArtistTable(Core::ITableModel *model)
{
    QString insertStatement = "INSERT INTO artist (id, artist) VALUES (?, ?)";
    QSqlQuery query(database);

    int genreCount = model->rowCount();
    int idIndex = model->indexOfColumn("id");
    int nameIndex = model->indexOfColumn("artist");

    for (int i = 0; i < genreCount; i++)
    {
        query.prepare(insertStatement);
        query.bindValue(0, model->data(model->index(i, idIndex)).toInt());
        query.bindValue(1, model->data(model->index(i, nameIndex)).toString());

        //if ( (genreCount % 10) == 0 )
        {
            qDebug() << "write Artist No. " << i;
            qDebug() << model->data(model->index(i, nameIndex)).toString();
            qDebug() << model->data(model->index(i, idIndex)).toInt();
        }

        if ( !query.exec() )
        {
            qDebug() << "ERROR: " << insertStatement << query.lastError();
            qDebug() << model->data(model->index(i, nameIndex)).toString();
            qDebug() << model->data(model->index(i, idIndex)).toInt();
            return false;
        }
    }

    return true;
}

bool AudioSQLStorageAdapter::writeAlbumTable(Core::ITableModel *model)
{
    QString insertStatement = "INSERT INTO album (id, album) VALUES (?, ?)";
    QSqlQuery query(database);

    int genreCount = model->rowCount();
    int idIndex = model->indexOfColumn("id");
    int nameIndex = model->indexOfColumn("album");

    for (int i = 0; i < genreCount; i++)
    {
        query.prepare(insertStatement);
        query.bindValue(0, model->data(model->index(i, idIndex)).toInt());
        query.bindValue(1, model->data(model->index(i, nameIndex)).toString());

        if ( !query.exec() )
        {
            qDebug() << "ERROR: " << insertStatement << query.lastError();
            return false;
        }
    }

    return true;
}

bool AudioSQLStorageAdapter::writeArtistToAlbumTable(Core::ITableModel *model)
{
    QString insertStatement = "INSERT INTO ArtistToAlbum VALUES (?, ?)";
    QSqlQuery query(database);

    int genreCount = model->rowCount();
    int artistIdIndex = model->indexOfColumn("artist_id");
    int albumIdIndex = model->indexOfColumn("album_id");

    for (int i = 0; i < genreCount; i++)
    {
        query.prepare(insertStatement);
        query.bindValue(0, model->data(model->index(i, artistIdIndex)).toInt());
        query.bindValue(1, model->data(model->index(i, albumIdIndex)).toInt());

        if ( !query.exec() )
        {
            qDebug() << "ERROR: " << insertStatement << query.lastError();
            return false;
        }
    }

    return true;
}

bool AudioSQLStorageAdapter::writeSongTable(Core::ITableModel *model)
{
    QString insertStatement = "INSERT INTO song (id, song, artist_id, genre_id, album_id, year, track_number, filename, length) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";
    QSqlQuery query(database);

    int genreCount = model->rowCount();
    int idIndex = model->indexOfColumn("id");
    int nameIndex = model->indexOfColumn("song");
    int artistIdIndex = model->indexOfColumn("artist_id");
    int genreIdIndex = model->indexOfColumn("genre_id");
    int albumIdIndex = model->indexOfColumn("album_id");
    int yearIndex = model->indexOfColumn("year");
    int trackIndex = model->indexOfColumn("track_number");
    int fileNameIndex = model->indexOfColumn("filename");
    int lengthIndex = model->indexOfColumn("length");

    for (int i = 0; i < genreCount; i++)
    {
        query.prepare(insertStatement);
        query.bindValue(0, model->data(model->index(i, idIndex)).toInt());
        query.bindValue(1, model->data(model->index(i, nameIndex)).toString());
        query.bindValue(2, model->data(model->index(i, artistIdIndex)).toInt());
        query.bindValue(3, model->data(model->index(i, genreIdIndex)).toInt());
        query.bindValue(4, model->data(model->index(i, albumIdIndex)).toInt());
        query.bindValue(5, model->data(model->index(i, yearIndex)).toInt());
        query.bindValue(6, model->data(model->index(i, trackIndex)).toInt());
        query.bindValue(7, model->data(model->index(i, fileNameIndex)).toString());
        query.bindValue(8, model->data(model->index(i, lengthIndex)).toInt());

        if ( !query.exec() )
        {
            qDebug() << "ERROR: " << insertStatement << query.lastError();
            return false;
        }
    }

    return true;
}

bool AudioSQLStorageAdapter::writeTableForDataItemType(Core::ITableModel *model, Core::DataItem::DATA_ITEM_TYPE type)
{
    switch(type)
    {
        case Core::DataItem::GENRE:
            return writeGenreTable(model);

        case Core::DataItem::ARTIST:
            return writeArtistTable(model);

        case Core::DataItem::ALBUM:
            return writeAlbumTable(model);

        case Core::DataItem::SONG:
            return writeSongTable(model);

        default:

            return false;
    }
}

bool AudioSQLStorageAdapter::writeTable(Core::ITableModel *model, QString table)
{
    if (table == "ArtistToAlbum")
    {
        writeArtistToAlbumTable(model);
        return true;
    }

    return false;
}
