#include "audiofile.h"
#include "taglib/mpegfile.h"

AudioFile::AudioFile(QString path)
    : MediaSource(path), tagsRead(false)
{
    this->path = path;
    QFileInfo pathInfo( this->fileName() );
        this->artist = pathInfo.fileName();
        this->track = 0;
}

AudioFile::AudioFile(int sID, QString sArtist, QString sTitle, QString sGenre, QString sAlbum, QString sComment, int sYear, int sTrack, QString path)
        : MediaSource(path), id(sID), artist(sArtist), title(sTitle), genre(sGenre), album(sAlbum), comment(sComment), year(sYear), track(sTrack)
{

}


int AudioFile::getId()
{
    tagsLock.lockForRead();
        int id = this->id;
    tagsLock.unlock();

    return id;
}

QString AudioFile::getArtist()
{
    tagsLock.lockForRead();
        QString artist = this->artist;
    tagsLock.unlock();

   return  artist;
}

QString AudioFile::getTitle()
{
    tagsLock.lockForRead();
        QString title = this->title;
    tagsLock.unlock();

    return title;
}

QString AudioFile::getGenre()
{
    tagsLock.lockForRead();
        QString genre = this->genre;
    tagsLock.unlock();

    return genre;
}

QString AudioFile::getAlbum()
{
    tagsLock.lockForRead();
        QString album = this->album;
    tagsLock.unlock();

    return album;
}

QString AudioFile::getComment()
{
    tagsLock.lockForRead();
        QString comment = this->comment;
    tagsLock.unlock();

    return comment;
}

int AudioFile::getYear()
{
    tagsLock.lockForRead();
        int year = this->year;
    tagsLock.unlock();

    return year;
}

int AudioFile::getTrack()
{
    tagsLock.lockForRead();
        int track = this->track;
    tagsLock.unlock();

    return track;
}


int AudioFile::getLength()
{
    tagsLock.lockForRead();

        int length = this->length;
    tagsLock.unlock();


   return length;
}

QString AudioFile::getLengthAsString()
{
    int length = this->getLength();
    int min =  length/60;
    int sec = length % 60;
    QString string;
    string = QString::number(min)+":"+QString("%1").arg(QString::number(sec),2,'0');


    return string;

}



int AudioFile::ReadTags()
{

    if (!tagsRead)
    {

        QByteArray fileName = QFile::encodeName( this->fileName() );

        QFileInfo* file = new QFileInfo(this->fileName());
        if (!file->exists())
        {
            qDebug()<<this->fileName()+" existiert nicht.";
            return -1;

        }
        else
        {

            const char * encodedName = fileName.constData();

            TagLib::FileRef ref = TagLib::FileRef( encodedName );

            tagsLock.lockForWrite();

                album = ref.tag()->album().toCString();
                artist = ref.tag()->artist().toCString();
                title = ref.tag()->title().toCString();
                track = ref.tag()->track();
                genre = ref.tag()->genre().toCString();
                comment = ref.tag()->comment().toCString();
                year = ref.tag()->year();
                length = ref.audioProperties()->length();



                QFileInfo pathInfo( this->fileName() );

                if (this->genre.trimmed().isEmpty()) genre ="Unbekannt";
                if (this->album.trimmed().isEmpty()) album ="Unbekannt";
                if (this->artist.trimmed().isEmpty()) artist ="Unbekannt";
                if (this->title.trimmed().isEmpty()) title = pathInfo.fileName();

            tagsLock.unlock();

        }
    }

    tagsRead = true;
    return 0;

}


bool AudioFile::setArtist(QString artist)
{
    QByteArray fileName = QFile::encodeName( this->fileName() );
    bool success;
    QFileInfo* file = new QFileInfo(this->fileName());
    if (file->exists())
    {
    const char * encodedName = fileName.constData();
    TagLib::Tag* tag;

    if (this->fileName().toLower().endsWith(QString(".mp3").toLower()))
        {
        TagLib::MPEG::File mpegfile(encodedName);

            tag = mpegfile.ID3v2Tag(true);
            tagsLock.lockForWrite();
            tag->setArtist(artist.toStdString());
            success = mpegfile.save();
            tagsLock.unlock();

        }
        else
        {

            TagLib::FileRef ref = TagLib::FileRef( encodedName );
            tag = ref.tag();
            tagsLock.lockForWrite();
            tag->setArtist(artist.toStdString());
            success = ref.save();
            tagsLock.unlock();

        }


        this->ReadTags();
        if (this->getTitle() != title) qDebug()<<"title Error";
        return success;

}

}



bool AudioFile::setTitle(QString title)
{
    QByteArray fileName = QFile::encodeName( this->fileName() );
    bool success;
    QFileInfo* file = new QFileInfo(this->fileName());
    if (file->exists())
    {
    const char * encodedName = fileName.constData();
    TagLib::Tag* tag;

        if (this->fileName().toLower().endsWith(QString(".mp3").toLower()))
        {
            TagLib::MPEG::File mpegfile(encodedName);

            tag = mpegfile.ID3v2Tag(true);
            tagsLock.lockForWrite();
            tag->setTitle(title.toStdString());
            success = mpegfile.save();
            tagsLock.unlock();
        }
        else
        {

            TagLib::FileRef ref = TagLib::FileRef( encodedName );
            tag = ref.tag();
            tagsLock.lockForWrite();
            tag->setTitle(title.toStdString());
            success = ref.save();
            tagsLock.unlock();
        }

        this->ReadTags();
        if (this->getTitle() != title) qDebug()<<"title Error";
        return success;
     }

}




bool AudioFile::setGenre(QString genre)
{
    QByteArray fileName = QFile::encodeName( this->fileName() );
    bool success;
    QFileInfo* file = new QFileInfo(this->fileName());
    if (file->exists())
    {
    const char * encodedName = fileName.constData();
    TagLib::Tag* tag;

    if (this->fileName().toLower().endsWith(QString(".mp3").toLower()))
        {
        TagLib::MPEG::File mpegfile(encodedName);

            tag = mpegfile.ID3v2Tag(true);
            tagsLock.lockForWrite();
            tag->setGenre(genre.toStdString());
            success = mpegfile.save();
            tagsLock.unlock();

        }
        else
        {

            TagLib::FileRef ref = TagLib::FileRef( encodedName );
            tag = ref.tag();
            tagsLock.lockForWrite();
            tag->setGenre(genre.toStdString());
            success = ref.save();
            tagsLock.unlock();

        }

        this->ReadTags();
        if (this->getGenre() != genre) qDebug()<<"genre Error";
        return success;

    }


return success;

}
bool AudioFile::setAlbum(QString album)
{
    QByteArray fileName = QFile::encodeName( this->fileName() );
    bool success;
    QFileInfo* file = new QFileInfo(this->fileName());
    if (file->exists())
    {
    const char * encodedName = fileName.constData();
    TagLib::Tag* tag;

    if (this->fileName().toLower().endsWith(QString(".mp3").toLower()))
        {
        TagLib::MPEG::File mpegfile(encodedName);

            tag = mpegfile.ID3v2Tag(true);
            tagsLock.lockForWrite();
            tag->setAlbum(album.toStdString());
            success = mpegfile.save();
            tagsLock.unlock();

        }
        else
        {

            TagLib::FileRef ref = TagLib::FileRef( encodedName );
            tag = ref.tag();
            tagsLock.lockForWrite();
            tag->setAlbum(album.toStdString());
            success = ref.save();
            tagsLock.unlock();

        }

        this->ReadTags();
        if (this->getAlbum() != album) qDebug()<<"genre Error";
        return success;

    }


return success;
}


bool AudioFile::setComment(QString comment)
{
    QByteArray fileName = QFile::encodeName( this->fileName() );
    bool success;
    QFileInfo* file = new QFileInfo(this->fileName());
    if (file->exists())
    {
    const char * encodedName = fileName.constData();
    TagLib::Tag* tag;

        if (this->fileName().toLower().endsWith(QString(".mp3").toLower()))
        {
            TagLib::MPEG::File mpegfile(encodedName);

            tag = mpegfile.ID3v2Tag(true);
            tagsLock.lockForWrite();
            tag->setComment(comment.toStdString());
            success = mpegfile.save();
            tagsLock.unlock();
        }
        else
        {

            TagLib::FileRef ref = TagLib::FileRef( encodedName );
            tag = ref.tag();
            tagsLock.lockForWrite();
            tag->setComment(comment.toStdString());
            success = ref.save();
            tagsLock.unlock();
        }

        this->ReadTags();
        if (this->getComment() != comment) qDebug()<<"title Error";

     }
return success;
}
