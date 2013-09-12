#ifndef SONG_H
#define SONG_H

#include "Media.h"
#include "Genre.h"
#include "Album.h"
#include "Artist.h"
#include "AlbumArtist.h"

namespace Core
{
    /**
        \brief  Data Transfer Object for songs

        This class stores and provides the information (such as title, year, artist, ...)
        for individual songs.
    */
    class COREPLUGINSHARED_EXPORT Song : public Media
    {
        Q_OBJECT
        public:
            explicit Song(int sID, QString sName, int year,  QObject *parent);
            explicit Song(int sID, QString sName, int year,  QString filename, QObject *parent);
            explicit Song(int sID, QString sName, int year,  QString filename, bool temporary, QObject *parent);

        signals:

        public slots:

            Artist*         getArtist();
            Album*          getAlbum();
            AlbumArtist*    getAlbumArtist();
            Genre*          getGenre();
            int             getYear();
            QString         getFileName();
            int             getTrack();
            int             getLength();

            void            setArtist(Artist* sArtist);
            void            setAlbum(Album* sAlbum);
            void            setGenre(Genre* sGenre);
            void            setAlbumArtist(AlbumArtist* albumartist);
            void            setTrack(int track);
            void            setLength(int length);

            /**
                \brief      Moves the song to a new artist and makes the
                            appropriate relationsships.
                \param      the new artist
                \returns    success of the operation
            */
            bool            moveToArtist(DataItem *newArtist);

            /**
                \brief      Moves to song to a new album and makes the
                            appropriate relationsships.
                \param      the new album
                \returns    success of the operation
            */
            bool            moveToAlbum(DataItem *newAlbum);

            bool            moveToGenre(DataItem *newGenre);

        public:

            QList<Media*>   getMedia();
            QUrl            getURL();
            QString         getMimeType();

        protected:

            Artist* interpret;
            AlbumArtist* albumArtist;
            Album* album;
            Genre* genre;
            QString filename;
            int year;
            int track;
            int length;
    };
}

#endif // SONG_H
