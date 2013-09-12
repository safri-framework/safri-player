#include "audiosqlstorage.h"
#include <sqlitestorage.h>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <Interfaces/ICore.h>
#include <QStringList>
#include "CoreData/Audio.h"
#include "Interfaces/IAudioCollection.h"
#include "Settings/SettingsManager.h"
#include <QFileInfo>
#include "SQLStatements.h"

using namespace Core;

AudioSQLStorage::AudioSQLStorage(QUrl url, QObject *parent) :
    IMediaCollectionStorage(parent), url(url), sqlStorage(new SQLiteStorage(url, this))
{
}

AudioSQLStorage::~AudioSQLStorage()
{
}

Core::IMediaCollection *AudioSQLStorage::loadMediaCollection()
{
    Core::IMediaCollection* mediaCollection;

    if ( !sqlStorage->open(ISQLStorage::READ) )
    {
        qDebug() << "Can't open database";
        return 0;
    }

    query = sqlStorage->createQuery();

    if ( !checkIfDatabaseExists() )
    {
        qDebug() << "Database tables don't exists. trying to create...";
        if ( !createDatabase() )
        {
            qDebug() << "Could not create database!";
            sqlStorage->close();
            return false;
        }

        if ( !checkIfDatabaseExists() )
        {
            qDebug() << "Database tables don't exists. givig up...";
            sqlStorage->close();
            return false;
        }
    }

    if ( !checkDatabaseVersion() )
    {
        qDebug() << "Database version mismatch";
        sqlStorage->close();
        return 0;
    }

    QString defaultCollectionName = Core::ICore::settingsManager()->getModule("org.safri.collection")->getSetting("defaultCollectionName").toString();
    mediaCollection = Core::ICore::createMediaCollection("org.safri.collection.audio", defaultCollectionName, QFileInfo(url.toString()).absolutePath());
    audioCollection = qobject_cast<Core::IAudioCollection*>(mediaCollection);

    if ( !audioCollection )
    {
        qDebug() << "Could not create media collection org.safri.collection.audio";
        sqlStorage->close();
        return 0;
    }

    audioCollection->setDatabaseLocation(url);

    if ( !loadGenres() )
    {
        qDebug() << "Could not load genres!";
        sqlStorage->close();
        return 0;
    }

    if ( !loadArtists() )
    {
        qDebug() << "Could not load artists!";
        sqlStorage->close();
        return 0;
    }

    if ( !loadAlbums() )
    {
        qDebug() << "Could not load albums!";
        sqlStorage->close();
        return 0;
    }

    if ( !loadSongs() )
    {
        qDebug() << "Could not load songs!";
        sqlStorage->close();
        return 0;
    }

    qDebug() << "Database loaded";
    sqlStorage->close();

    return audioCollection;
}

bool AudioSQLStorage::saveMediaCollection(Core::IMediaCollection *collection)
{
    qDebug() << "AudioSQLStorage::saveMediaCollection()";

    audioCollection = qobject_cast<Core::IAudioCollection*>(collection);

    if (audioCollection)
    {

        if ( !sqlStorage->open(ISQLStorage::WRITE) )
        {
            qDebug() << "Cannot open database for write!";
            sqlStorage->close();
            return false;
        }

        query = sqlStorage->createQuery();

        if ( !checkIfDatabaseExists() )
        {
            qDebug() << "Database tables don't exists. trying to create...";
            if ( !createDatabase() )
            {
                qDebug() << "Could not create database!";
                sqlStorage->close();
                return false;
            }

            if ( !checkIfDatabaseExists() )
            {
                qDebug() << "Database tables don't exists. givig up...";
                sqlStorage->close();
                return false;
            }
        }

        if ( !query.exec("BEGIN") )
        {
            qDebug() << "ERROR: " << "BEGIN" << query.lastError();
            return false;
        }

        qDebug() << "saveGenres";
        if ( !saveGenres() )
        {
           qDebug() << "Could not save genres!";
           sqlStorage->close();
           return false;
        }

        qDebug() << "saveArtists";
        if ( !saveArtists() )
        {
           qDebug() << "Could not save artists!";
           sqlStorage->close();
           return false;
        }

        qDebug() << "saveAlbums";
        if ( !saveAlbums() )
        {
           qDebug() << "Could not save albums!";
           sqlStorage->close();
           return false;
        }

        qDebug() << "saveSongs";
        if ( !saveSongs() )
        {
           qDebug() << "Could not save songs!";
           sqlStorage->close();
           return false;
        }

        if ( !query.exec("COMMIT") )
        {
            qDebug() << "ERROR: " << "COMMIT" << query.lastError();
            return false;
        }

        sqlStorage->close();
        return true;
    }
    else
    {
        qDebug() << "Cannot save this type of media collection";
        return false;
    }

    return false;
}

QString AudioSQLStorage::getStorageType()
{
    return "org.safri.sqlite.audio";
}

bool AudioSQLStorage::checkIfDatabaseExists()
{
    if ( !query.exec(STMT_DATABASE_EXISTS))
    {
        qDebug() << "ERROR: " << STMT_DATABASE_EXISTS << query.lastError();
        return false;
    }

    query.next();

    int tableCount = query.value(0).toInt();

    return tableCount > 0;
}

bool AudioSQLStorage::checkDatabaseVersion()
{
    if ( !query.exec(STMT_DATABASE_VERSION) )
    {
        qDebug() << "ERROR: " << STMT_DATABASE_VERSION << query.lastError();
        return false;
    }

    query.next();

    int databaseVersion = query.value( query.record().indexOf("DATABASE_VERSION") ).toInt();

    return databaseVersion >= DATABASE_VERSION;
}

bool AudioSQLStorage::loadGenres()
{
    if ( !query.exec(STMT_SELECT_GENRES) )
    {
        qDebug() << "ERROR: " << STMT_SELECT_GENRES << query.lastError();
        return false;
    }

    int idIndex = query.record().indexOf("ID");
    int nameIndex = query.record().indexOf("GENRE");
    Genre* genre;
    int id;
    QString name;

    while ( query.next() )
    {
        id = query.value(idIndex).toInt();
        name = query.value(nameIndex).toString();

        //qDebug() << id << ": " << name;
        genre = new Genre(id, name, audioCollection);

        audioCollection->insertGenre(genre);
    }

    return true;
}

bool AudioSQLStorage::loadArtists()
{
    if ( !query.exec(STMT_SELECT_ARTISTS) )
    {
        qDebug() << "ERROR: " << STMT_SELECT_ARTISTS << query.lastError();
        return false;
    }

    int idIndex = query.record().indexOf("ID");
    int nameIndex = query.record().indexOf("ARTIST");
    Artist* artist;
    int id;
    QString name;

    while ( query.next() )
    {
        id = query.value(idIndex).toInt();
        name = query.value(nameIndex).toString();

        //qDebug() << id << ": " << name;
        artist = new Artist(id, name, audioCollection);

        audioCollection->insertArtist(artist);
    }

    return true;
}

QMap<int, int> AudioSQLStorage::loadArtistToAlbumMap()
{
    QMap<int, int> artistToAlbumMap;

    if ( !query.exec(STMT_SELECT_ARTIST_ALBUM))
    {
        qDebug() << "ERROR: " << STMT_SELECT_ARTIST_ALBUM << query.lastError();
    }

    int artist_id, album_id;
    int albumIndex = query.record().indexOf("album_id");
    int artistIndex = query.record().indexOf("artist_id");

    while ( query.next() )
    {
        album_id = query.value( albumIndex ).toInt();
        artist_id = query.value( artistIndex ).toInt();

        artistToAlbumMap.insertMulti(album_id, artist_id);
    }

    return artistToAlbumMap;
}

bool AudioSQLStorage::loadAlbums()
{
    QMap<int, int> artistToAlbumMap = loadArtistToAlbumMap();

    if ( !query.exec(STMT_SELECT_ALBUMS) )
    {
        qDebug() << "ERROR: " << STMT_SELECT_ALBUMS << query.lastError();
        return false;
    }

    int idIndex = query.record().indexOf("ID");
    int nameIndex = query.record().indexOf("ALBUM");
    Album* album;
    int id;
    QString name;
    Artist* artist;
    QList<int> artistIDs;
    int numberOfArtists;

    while ( query.next() )
    {
        id = query.value(idIndex).toInt();
        name = query.value(nameIndex).toString();

        //qDebug() << id << ": " << name;
        album = new Album(id, name, audioCollection);

        artistIDs = artistToAlbumMap.values(id);
        numberOfArtists = artistIDs.size();

        for (int i = 0; i < numberOfArtists; i++)
        {
            artist = audioCollection->getArtistByID(artistIDs.at(i));

            if (artist != 0)
            {
                artist->addAlbum(album);
                album->addArtist( artist );
            }

        }

        audioCollection->insertAlbum(album);
    }

    return true;
}

bool AudioSQLStorage::loadSongs()
{
    if ( !query.exec(STMT_SELECT_SONGS) )
    {
        qDebug() << "ERROR: " << STMT_SELECT_SONGS << query.lastError();
        return false;
    }

    int idIndex = query.record().indexOf("ID");
    int nameIndex = query.record().indexOf("SONG");
    int artistIndex = query.record().indexOf("artist_id");
    int genreIndex = query.record().indexOf("genre_id");
    int albumIndex = query.record().indexOf("album_id");
    int yearIndex = query.record().indexOf("year");
    int trackIndex = query.record().indexOf("track_number");
    int lengthIndex = query.record().indexOf("length");
    int filenameIndex = query.record().indexOf("filename");

    int artistID, genreID, albumID, year, track, length;
    QString filename;

    Artist* artist;
    Genre* genre;
    Album* album;
    Song* song;
    int id;
    QString name;

    while ( query.next() )
    {
        id = query.value(idIndex).toInt();
        name = query.value(nameIndex).toString();
        artistID = query.value(artistIndex).toInt();
        genreID = query.value(genreIndex).toInt();
        albumID = query.value(albumIndex).toInt();
        year = query.value(yearIndex).toInt();
        track = query.value(trackIndex).toInt();
        length = query.value(lengthIndex).toInt();
        filename = query.value(filenameIndex).toString();

        song = new Song(id, name, year, filename, audioCollection);
        song->setLength(length);

        artist = audioCollection->getArtistByID(artistID);
        genre = audioCollection->getGenreByID(genreID);
        album = audioCollection->getAlbumByID(albumID);

        genre->addSong(song);
        album->addSong(song);

        song->setAlbum(album);
        song->setArtist(artist);
        song->setGenre(genre);
        song->setTrack(track);

        audioCollection->insertSong(song);
    }

    return true;
}

bool AudioSQLStorage::createDatabase()
{
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

bool AudioSQLStorage::saveGenres()
{
    QList<Genre*> genres = audioCollection->getGenres();
    Genre* genre;

    int genreCount = genres.size();

    for (int i = 0; i < genreCount; i++)
    {
        genre = genres.at(i);
        //qDebug() << genre->getID() << ": " << genre->getName();

        query.prepare( STMT_INSERT_GENRE );
        query.bindValue( 0, genre->getID() );
        query.bindValue( 1, genre->getName() );

        if ( !query.exec() )
        {
            qDebug() << "ERROR: " << STMT_INSERT_GENRE << query.lastError();
            return false;
        }
    }

    return true;
}

bool AudioSQLStorage::saveArtists()
{
    QList<Artist*> artists = audioCollection->getArtists();
    Artist* artist;

    int artistCount = artists.size();

    for (int i = 0; i < artistCount; i++)
    {
        artist = artists.at(i);

        if ( artist->getID() == -1 )
        {
            continue;
        }

        //qDebug() << artist->getID() << ": " << artist->getName();

        query.prepare( STMT_INSERT_ARTIST );
        query.bindValue( 0, artist->getID() );
        query.bindValue( 1, artist->getName() );

        if ( !query.exec() )
        {
            qDebug() << "ERROR: " << STMT_INSERT_ARTIST << query.lastError();
            return false;
        }
    }

    return true;
}

bool AudioSQLStorage::saveAlbums()
{
    QList<Album*> albums = audioCollection->getAlbums();
    QList<Artist*> artists;
    Artist* artist;
    Album* album;
    int albumToArtistCount;

    int albumCount = albums.size();

    for (int i = 0; i < albumCount; i++)
    {
        album = albums.at(i);

        //qDebug() << album->getID() << ": " << album->getName();

        query.prepare( STMT_INSERT_ALBUM );
        query.bindValue( 0, album->getID() );
        query.bindValue( 1, album->getName() );

        if ( !query.exec() )
        {
            qDebug() << "ERROR: " << STMT_INSERT_ALBUM << query.lastError();
            return false;
        }

        artists = album->getArtists();
        albumToArtistCount = artists.size();

        for (int j = 0; j < albumToArtistCount; j++)
        {
            artist = artists.at(j);

            query.prepare( STMT_INSERT_ARTIST_ALBUM );
            query.bindValue( 0, artist->getID() );
            query.bindValue( 1, album->getID() );

            if ( !query.exec() )
            {
                qDebug() << "ERROR: " << STMT_INSERT_ARTIST_ALBUM << query.lastError();
                return false;
            }
        }
    }

    return true;
}

bool AudioSQLStorage::saveSongs()
{
    QList<Song*> songs = audioCollection->getSongs();
    Song* song;

    int songCount = songs.size();

    for (int i = 0; i < songCount; i++)
    {
        song = songs.at(i);

        //qDebug() << song->getID() << ": " << song->getName();

        query.prepare( STMT_INSERT_SONG );
        query.bindValue( 0, song->getID() );
        query.bindValue( 1, song->getName() );
        query.bindValue( 2, song->getArtist()->getID() );
        query.bindValue( 3, song->getGenre()->getID() );
        query.bindValue( 4, song->getAlbum()->getID() );
        query.bindValue( 5, song->getYear() );
        query.bindValue( 6, song->getTrack() );
        query.bindValue( 7, song->getFileName() );
        query.bindValue( 8, song->getLength() );

        if ( !query.exec() )
        {
            qDebug() << "ERROR: " << STMT_INSERT_SONG << query.lastError();
            return false;
        }
    }

    return true;
}
