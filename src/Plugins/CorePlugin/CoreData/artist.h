#ifndef ARTIST_H
#define ARTIST_H

#include "dataitem.h"
#include <QList>
#include <QMap>
#include "../CorePlugin_global.h"
namespace Core
{
    class Album;

    class COREPLUGINSHARED_EXPORT Artist : public DataItem
    {
        Q_OBJECT
        public:

            explicit Artist(int sID, QString sName, QObject *parent = 0);
            explicit Artist(int sID, QString sName,bool temporary ,QObject *parent = 0);
            explicit Artist(Artist* artist, QObject *parent = 0);

            QList<Album*>& getAlbums();
            QList<Album*> getAlbumByName(QString name);
             QList<Media*> getMedia();

        public slots:

            void addAlbum(Album* album);
            void removeAlbum(Album* album);

        private:

            QList<Album*> albums;
    };
}

#endif // ARTIST_H
