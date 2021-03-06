#ifndef ALBUM_H
#define ALBUM_H

#include "Artist.h"
#include "AlbumArtist.h"
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

            static void sortByYear(QList<Album *> &albums);

        public slots:

            void addArtist(Artist* sArtist);
            void setAlbumArtist(AlbumArtist* albumartist);
            AlbumArtist* getAlbumArtist();
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

            QList<Media*> getMedia();

        private:
            AlbumArtist* albumArtist;
            QSet<Artist*> artists;
            QString albumCoverFile;

            QList<Song*> songs;

            static bool albumYearLessThan(Album* album1, Album* album2);
    };
}

#endif // ALBUM_H
