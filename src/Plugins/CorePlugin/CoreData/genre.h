#ifndef GENRE_H
#define GENRE_H

#include "../CorePlugin_global.h"

#include "basedto.h"
#include <QList>
#include <QMap>

namespace Core
{
    class Song;

    class COREPLUGINSHARED_EXPORT Genre : public BaseDTO
    {
        Q_OBJECT
        public:
            explicit Genre(int sID, QString sName, QObject *parent = 0);
            explicit Genre(int sID, QString sName, bool temporary, QObject *parent = 0);
            explicit Genre(Genre* genre, QObject *parent = 0);

        signals:

        public slots:

            void addSong(Song* song);
            void removeSong(Song* song);

            QList<Song*> getSongs();

        public:

            /**
                \brief      Provides access to genres by their name
                \param      the name of the genre
                \returns    the genre which is associated with the given name
              */
            static Genre* getByName(QString name);



            static QList<Genre*> getAll();

            /**
                \brief      Provides access to genres by their id
                \param      the id of the genre
                \returns    the genre which is associated with the given id
              */
            static Genre* getByID(int id);

            /**
                \brief      Adds a genre to the interal maps for accessing them
                            by their specific keys (i.e. id, name, etc.)
                \param      the genre object
              */
            static void add(Genre* genre);

            /**
                \brief      Removes a genre from the interal accessor maps
                \param      the genre object
              */
            static void remove(Genre* genre);

            /**
                \brief      Generates a new genre id
                \return     the new generated genre id
              */
            static int createNewID();

            //! Static integer for the latest used ID
            static int latestID;

        protected:

            QList<Song*> songs;

        private:

            //! Static map for accessing genres by their names
            static QMap<QString, Genre*> genresByName;

            //! Static map for accessing genres by their id
            static QMap<int, Genre*> genresByID;

    };
}

#endif // GENRE_H
