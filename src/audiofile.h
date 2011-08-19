#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <phonon/mediasource.h>
#include <QFileInfo>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <QTime>
#include <QReadWriteLock>

/**
    \brief  This class represents a physical audio file.

    It's subclassed from Phonon::MediaSource so it can be directly attatched
    to the Phonon media object. AudioFile also provides methods for accessing
    audio file meta tags.
*/
class AudioFile : public Phonon::MediaSource
{
    private:

        int id;
        QString artist;
        QString title;
        QString genre;
        QString album;
        QString comment;
        int length;

        bool tagsRead;

        int year;
        int track;

        QReadWriteLock tagsLock;


    public:
        QString path;
        AudioFile(QString path);
        AudioFile(int sID, QString sArtist, QString sTitle, QString sGenre, QString sAlbum, QString sComment, int sYear, int sTrack, QString path);

        int getId();

        QString getArtist();
        QString getTitle();
        QString getGenre();
        QString getAlbum();
        QString getComment();

        bool setArtist(QString artist);
        bool setTitle(QString title);
        bool setGenre(QString genre);
        bool setAlbum(QString album);
        bool setComment(QString comment);


        int getLength();
        QString getLengthAsString();
        int getYear();
        int getTrack();

        /**
          \brief Reads the Meta-Tags of the audio file

            This method reads the meta-tags (artist, title, album, track, genre,
            comment, year) of the audio file. It first checks if the tags are
            already read, so the tags won't be read twice. Empty meta-tags will
            be filled with "Unbekannt". Calling this method is thread-safe!
        */
        int ReadTags();
};

#endif // AUDIOFILE_H
