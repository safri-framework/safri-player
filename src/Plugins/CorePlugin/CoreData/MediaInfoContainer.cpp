#include "MediaInfoContainer.h"
#include <QJsonDocument>

using namespace Core;

MediaInfoContainer::MediaInfoContainer(QUrl mediaUrl, QObject *parent)
    : QObject(parent), mediaUrl(mediaUrl)
{

}

MediaInfoContainer::MediaInfoContainer(const MediaInfoContainer &other)
    : QObject( other.parent() ), mediaUrl(other.mediaUrl), infoMap(other.infoMap)
{

}

void MediaInfoContainer::setMediaInfo(MediaInfoType type, QVariant info)
{
    infoMap.insert(typeToString(type), info);
}

QVariant MediaInfoContainer::getMediaInfo(MediaInfoType type)
{
    QVariant value =  infoMap.value(typeToString(type));
    if(!value.isValid())
    {
        if(type == InfoMimeType)
            return "audio/mpeg";
        else
            return tr("Unbekannt");
    }

    return value;
}

QUrl MediaInfoContainer::getURL()
{
    return this->mediaUrl;
}

QString MediaInfoContainer::toJson()
{
    return QJsonDocument::fromVariant(infoMap).toJson();
}

MediaInfoContainer MediaInfoContainer::fromJson(QString json)
{
    MediaInfoContainer container;
    QJsonParseError error;
    QVariantMap map = QJsonDocument::fromJson(json.toUtf8(), &error).toVariant().toMap();
    if(error.error == QJsonParseError::NoError)
        container.infoMap = map;

    return container;
}


QString MediaInfoContainer::typeToString(MediaInfoType type)
{
    switch(type)
    {
        case InfoAlbum:
            return "Album";
        case InfoArtist:
            return "Artist";
        case InfoAlbumArtist:
            return "AlbumArtist";
        case InfoBitRate:
            return "BitRate";
        case InfoFileSize:
            return "FileSize";
        case InfoGenre:
            return "Genre";
        case InfoLength:
            return "Length";
        case InfoMimeType:
            return "MimeType";
        case InfoTemporary:
            return "Temporary";
        case InfoTitle:
            return "Title";
        case InfoTrack:
            return "Track";
        case InfoURL:
            return "URL";
        case InfoYear:
            return "Year";
    }
}

MediaInfoType MediaInfoContainer::stringToType(QString string)
{
    if (string == "Album")
        return InfoAlbum;
    if (string == "Artist")
        return InfoArtist;
    if (string == "AlbumArtist")
        return InfoAlbumArtist;
    if (string == "BitRate")
        return InfoBitRate;
    if (string == "FileSize")
        return InfoFileSize;
    if (string == "Genre")
        return InfoGenre;
    if (string == "Length")
        return InfoLength;
    if (string == "MimeType")
        return InfoMimeType;
    if (string == "Temporary")
        return InfoTemporary;
    if (string == "Title")
        return InfoTitle;
    if (string == "Track")
        return InfoTrack;
    if (string == "URL")
        return InfoURL;
    if (string == "Year")
        return InfoYear;

    return NONE;
}
