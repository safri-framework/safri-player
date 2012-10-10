#ifndef ARTIST_H
#define ARTIST_H

#include "dataitem.h"
#include <QList>
#include <QMap>

namespace Core
{
    class Album;

    class Artist : public DataItem
    {
        Q_OBJECT
        public:

            explicit Artist(int sID, QString sName, QObject *parent = 0);
            explicit Artist(int sID, QString sName,bool temporary ,QObject *parent = 0);
            explicit Artist(Artist* artist, QObject *parent = 0);

        public slots:

            QList<Album*> &getAlbums();
            QList<Album*> getAlbumByName(QString name);
            void addAlbum(Album* album);
            void removeAlbum(Album* album);

        public:

            /**
                \brief      Provides access to artists by their name
                \param      the name of the artist
                \returns    the artist which is associated with the given name
            */
            static Artist* getByName(QString name);

            /**
                \brief      Provides access to artists by their id
                \param      the id of the artist
                \returns    the artist which is associated with the given id
            */
            static Artist* getByID(int id);

            static QList<Artist*> getAll();

            /**
                \brief      Adds an artist to the interal maps for accessing them
                            by their specific keys (i.e. id, name, etc.)
                \param      the artist object
            */
            static void add(Artist* artist);

            /**
                \brief      Removes an artist from the interal accessor maps
                \param      the artist object
            */
            static void remove(Artist* artist);

            /**
                \brief      Generates a new artist id
                \return     the new generated artist id
            */
            static int createNewID();

            //! Static integer for the latest used ID
            static int latestID;

            QList<Media*> getMedia();

        private:

            QList<Album*> albums;

            //! Static map for accessing albums by their names
            static QMap<QString, Artist*> artistsByName;

            //! Static map for accessing albums by their id
            static QMap<int, Artist*> artistsByID;

    };
}

#endif // ARTIST_H
