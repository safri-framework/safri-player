#ifndef SQLSTATEMENTS_H
#define SQLSTATEMENTS_H

#include <QString>

QString STMT_DATABASE_EXISTS        = "SELECT COUNT(type) FROM sqlite_master WHERE type='table' AND name='Artist';";
QString STMT_DATABASE_VERSION       = "SELECT DATABASE_VERSION FROM DATABASE_INFO;";
QString STMT_SELECT_GENRES          = "SELECT * FROM GENRE;";
QString STMT_SELECT_ARTISTS         = "SELECT * FROM ARTIST;";
QString STMT_SELECT_ARTIST_ALBUM    = "SELECT album_id, artist_id FROM ArtistToAlbum";
QString STMT_SELECT_ALBUMS          = "SELECT * FROM ALBUM;";
QString STMT_SELECT_SONGS           = "SELECT ID, SONG, artist_id, genre_id, album_id, year, filename, track_number, length FROM SONG;";
QString STMT_INSERT_GENRE           = "INSERT INTO genre VALUES (?, ?)";
QString STMT_INSERT_ARTIST          = "INSERT INTO ARTIST (id, artist) VALUES (?, ?)";
QString STMT_INSERT_ALBUM           = "INSERT INTO ALBUM (id, album) VALUES (?, ?)";
QString STMT_INSERT_ARTIST_ALBUM    = "INSERT INTO ArtistToAlbum VALUES (?, ?)";
QString STMT_INSERT_SONG            = "INSERT INTO song (id, song, artist_id, genre_id, album_id, year, track_number, filename, length) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";

#endif // SQLSTATEMENTS_H
