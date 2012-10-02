#ifndef SONG_H
#define SONG_H

#include "basedto.h"
#include "genre.h"
#include "album.h"
#include "artist.h"

namespace Core
{
    /**
        \brief  Data Transfer Object for songs

        This class stores and provides the information (such as title, year, artist, ...)
        for individual songs.
    */
    class Song : public BaseDTO
    {
        Q_OBJECT
        public:
            explicit Song(int sID, QString sName, int year,  QObject *parent);
            explicit Song(int sID, QString sName, int year,  QString filename, QObject *parent);
            explicit Song(int sID, QString sName, int year,  QString filename, bool temporary, QObject *parent);

        signals:

        public slots:

            Artist* getArtist();
            Album* getAlbum();

            Genre* getGenre();
            int getYear();
            QString getFileName();
            int getTrack();
            int getLength();

            void setInterpret(Artist* sInterpret);
            void setAlbum(Album* sAlbum);
            void setGenre(Genre* sGenre);
            void setTrack(int track);
            void setLength(int length);

            /**
                \brief      Moves the song to a new artist and makes the
                            appropriate relationsships.
                \param      the new artist
                \returns    success of the operation
            */
            bool moveToArtist(BaseDTO *newArtist);

            /**
                \brief      Moves to song to a new album and makes the
                            appropriate relationsships.
                \param      the new album
                \returns    success of the operation
            */
            bool moveToAlbum(BaseDTO *newAlbum);

            bool moveToGenre(BaseDTO *newGenre);

        public:

            /**
                \brief      Provides access to songs by their name
                \param      the name of the song
                \returns    the song which is associated with the given name
            */
            static QList<Song*> getByName(QString name);

            /**
                \brief      Provides access to songs by their id
                \param      the id of the song
                \returns    the song which is associated with the given id
            */
            static Song* getByID(int id);

            /**
                \brief      Provides access to songs by their path
                \param      the path of the song
                \returns    the song which is associated with the given path
            */
            static Song* getByPath(QString path);

            /**
                \brief      Adds an song to the interal maps for accessing them
                            by their specific keys (i.e. id, name, etc.)
                \param      the song object
              */
            static void add(Song* song);

            /**
                \brief      Removes an song from the interal accessor maps
                \param      the song object
            */
            static void remove(Song* song);

            /**
                \brief      Provides access to all Songs
                \param      the list with songs
            */
            static QList<Song*> getAll();

            /**
                \brief      Generates a new song id
                \return     the new generated song id
            */
            static int createNewID();

            //! Static integer for the latest used ID
            static int latestID;


        private:

            Artist* interpret;
            Album* album;
            Genre* genre;
            QString filename;
            int year;
            int track;
            int length;

            //! Static map for accessing songs by their names
            static QMap<QString, Song*> songsByName;

            //! Static map for accessing songs by their id
            static QMap<int, Song*> songsByID;

            //! Static map for accessing songs by their path
            static QMap<QString, Song*> songsByPath;
    };
}

#endif // SONG_H
