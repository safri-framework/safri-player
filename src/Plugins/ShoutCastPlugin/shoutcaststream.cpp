#include "shoutcaststream.h"

ShoutCastStream::ShoutCastStream(QString name, QString URL):Media(-1, name, Core::DataItem::AUDIO_STREAM, true), url(URL)
{
}

QUrl ShoutCastStream::getURL()
{
    return QUrl(url);
}

QString ShoutCastStream::getMimeType()
{
    return "audio/mpeg";
}

QList<Media *> ShoutCastStream::getMedia()
{
    QList<Media*> list;
    list.append(this);
    return list;
}
