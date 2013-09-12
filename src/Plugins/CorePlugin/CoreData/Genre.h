#ifndef GENRE_H
#define GENRE_H

#include "../CorePlugin_global.h"

#include "DataItem.h"
#include <QList>
#include <QMap>

namespace Core
{
    class Song;

    class COREPLUGINSHARED_EXPORT Genre : public DataItem
    {
        Q_OBJECT
        public:

            explicit Genre(int sID, QString sName, QObject *parent = 0);
            explicit Genre(int sID, QString sName, bool temporary, QObject *parent = 0);
            explicit Genre(Genre* genre, QObject *parent = 0);

            QList<Media*> getMedia();

        public slots:

            void addSong(Song* song);
            void removeSong(Song* song);
            QList<Song*> getSongs();

        protected:

            QList<Song*> songs;

    };
}

#endif // GENRE_H
