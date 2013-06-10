#ifndef ALBUMARTIST_H
#define ALBUMARTIST_H

#include "dataitem.h"
#include <QList>
#include <QMap>
#include "../CorePlugin_global.h"
namespace Core
{
    class Album;

    class COREPLUGINSHARED_EXPORT AlbumArtist : public DataItem
    {
        Q_OBJECT
        public:

            explicit AlbumArtist(int sID, QString sName, QObject *parent = 0);
            explicit AlbumArtist(int sID, QString sName,bool temporary ,QObject *parent = 0);
            explicit AlbumArtist(AlbumArtist* AlbumArtist, QObject *parent = 0);

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

#endif // ALBUMARTIST_H
