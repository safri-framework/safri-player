#include "taglibmediatagger.h"
#include <QFile>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <QVariant>
using namespace Core;
TaglibMediaTagger::TaglibMediaTagger(QObject *parent):IMediaTagger(parent)
{


}

void TaglibMediaTagger::tagMedia(QUrl media)
{


        QByteArray filename = QFile::encodeName( media.toString() );

        QString album;
        QString artist ;
        QString title ;
        QString genre ;
        QString comment ;
        int track;
        int year;
        int length;
        int bitRate;


        const char * encodedName = filename.constData();

            TagLib::FileRef ref = TagLib::FileRef( encodedName );
        if (ref.file()->isValid())
        {


            album = ref.tag()->album().toCString();
            artist = ref.tag()->artist().toCString();
            title = ref.tag()->title().toCString();
            genre = ref.tag()->genre().toCString();
            year = ref.tag()->year();
            track = ref.tag()->track();
            length = ref.audioProperties()->length();
            bitRate = ref.audioProperties()->bitrate();
            comment = ref.tag()->comment();


        }
        else
        {
            qDebug()<<"File Error";
            Q_EMIT unknownMedia(media);
        }

        QFileInfo pathInfo( fileName );

        if (genre.trimmed().isEmpty()) genre ="Unbekannt";
        if (album.trimmed().isEmpty()) album ="Unbekannt";
        if (artist.trimmed().isEmpty()) artist ="Unbekannt";
        if (title.trimmed().isEmpty()) title = pathInfo.fileName();

        MediaInfoContainer container(media);
        container.setMediaInfo(InfoArtist, artist);
        container.setMediaInfo(InfoAlbum, album);
        container.setMediaInfo(InfoGenre, genre);
        container.setMediaInfo(InfoTitle, title);
        container.setMediaInfo(InfoTrack, track);
        container.setMediaInfo(InfoLength, length);
        container.setMediaInfo(InfoFile);
       // Q_EMIT mediaTagged(container);



}

