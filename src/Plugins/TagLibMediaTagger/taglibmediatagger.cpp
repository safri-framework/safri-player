#include "taglibmediatagger.h"
#include <QFile>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2header.h>
#include <QVariant>
#include <QDebug>
#include <QFileInfo>

using namespace Core;


TaglibMediaTagger::TaglibMediaTagger(QObject *parent):IMediaTagger(parent)
{


}

TaglibMediaTagger::~TaglibMediaTagger()
{
    qDebug() << "TagLibMediaTagger destroyed";
}

void TaglibMediaTagger::tagMedia(QUrl media)
{
        QByteArray filename = QFile::encodeName( media.toString() );
        QString album;
        QString artist ;
        QString title ;
        QString genre ;
        QString comment ;
        QString albumartist;
        int track;
        int year;
        int length;
        int bitRate;

        Q_UNUSED(bitRate)

        const char * encodedName = filename.constData();
        TagLib::FileRef ref = TagLib::FileRef( encodedName );
        if (ref.file()->isValid())
        {
            TagLib::Tag* tag = ref.tag();

            album   =QString::fromUtf8( tag->album().toCString(true));
            artist  =QString::fromUtf8( tag->artist().toCString(true));
            title   =QString::fromUtf8( tag->title().toCString(true));
            genre   =QString::fromUtf8( tag->genre().toCString(true));
            year    = tag->year();
            track   = tag->track();
            length  = ref.audioProperties()->length();
            bitRate = ref.audioProperties()->bitrate();
            comment =QString::fromUtf8( tag->comment().toCString(true));
        }
        else
        {
            qDebug()<<"File Error";
            Q_EMIT unknownMedia(media);
            return;
        }

        QFileInfo pathInfo( filename );
        if (genre.trimmed().isEmpty()) genre    =tr("Unbekannt");
        if (album.trimmed().isEmpty()) album    =tr("Unbekannt");
        if (artist.trimmed().isEmpty()) artist  =tr("Unbekannt");
        if (title.trimmed().isEmpty()) title    = pathInfo.fileName();

        if (media.toString().toLower().endsWith(QString(".mp3").toLower()))
        {
            //TagLib::MPEG::File mpegfile(encodedName);
            TagLib::MPEG::File file(encodedName);
            TagLib::ByteVector handle = "TPE2";
            //TagLib::String value = "bar";
            TagLib::ID3v2::Tag *tag = file.ID3v2Tag(true);
            if(!tag->frameList(handle).isEmpty())
            {
                TagLib::ID3v2::Frame* frame = tag->frameListMap()["TPE2"].front();
                albumartist = QString(frame->toString().toCString());
            }
            else
            {
               albumartist = artist;
            }
        }

        MediaInfoContainer container(media);
        container.setMediaInfo(InfoArtist, artist);
        container.setMediaInfo(InfoAlbum, album);
        container.setMediaInfo(InfoGenre, genre);
        container.setMediaInfo(InfoTitle, title);
        container.setMediaInfo(InfoTrack, track);
        container.setMediaInfo(InfoLength, length);
        container.setMediaInfo(InfoYear, year);
        container.setMediaInfo(InfoAlbumArtist, albumartist);
        //container.setMediaInfo(InfoFile);
        Q_EMIT mediaTagged(container);
}

