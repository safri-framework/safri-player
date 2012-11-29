#ifndef ALBUM_H
#define ALBUM_H

#include "artist.h"
#include <QList>
#include <QSet>
#include <QMap>
#include "../CorePlugin_global.h"

namespace Core
{
    class Song;

    /**
        \brief  Data Transfer Object for albums

        This class stores and provides the information (such as name, artist, ...)
        for individual albums.
    */


    class COREPLUGINSHARED_EXPORT Album : public DataItem
    {
        Q_OBJECT
        public:
            explicit Album(int sID, QString sName, QObject *parent = 0);
            explicit Album(int sID, QString sName, bool temporary, QObject *parent = 0);
            explicit Album(Album* album, QObject *parent = 0);

        signals:

        public slots:

            void addArtist(Artist* sArtist);
            bool removeArtist(Artist* sArtist);
            QList<Artist*> getArtists();
            QList<Song*> getSongs();

            void addSong(Song* song);
            void removeSong(Song* song);

            bool isCompilation();

            QString getCoverFile();
            void setCoverFile(QString sCoverFile);

            /**
                \brief      Separates all songs from the given artist to an own album object. If the artist doesn't
                            have an appropriate album yet, a new album will be created.
                \param      the artist to separate
                \returns    the album to which the songs were separated
            */
            Album* separateArtist(DataItem* artist);

        public:

            /**
                \brief      Provides access to albums by their name
                \param      the name of the album
                \returns    the albums which are associated with the given name
            */
            static QList<Album*> getByName(QString name);

            /**
                \brief      Provides access to albums by their id
                \param      the id of the album
                \returns    the album which is associated with the given id
            */
            static Album* getByID(int id);

            /**
                \brief      Access to all existing albums.
                \returns    a QList list with all Albums.
            */
            static QList<Album*> getAll();

            /**
                \brief      Adds an album to the interal maps for accessing them
                            by their specific keys (i.e. id, name, etc.)
                \param      the album object
            */
            static void add(Album* album);

            /**
                \brief      Removes an album from the interal accessor maps
                \param      the album object
            */
            static void remove(Album* album);

            /**
                \brief      Generates a new album id
                \return     the new generated album id
            */
            static int createNewID();

            //! Static integer for the latest used ID
            static int latestID;

            QList<Media*> getMedia();


        private:

            QSet<Artist*> artists;
            QString albumCoverFile;

            QList<Song*> songs;

            //! Static map for accessing albums by their names
            static QMap<QString, Album*> albumsByName;

            //! Static map for accessing albums by their id
            static QMap<int, Album*> albumsByID;

    };
}

#endif // ALBUM_H
