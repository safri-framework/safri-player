#include "LastFMInfoResolver.h"
#include <QStringList>
#include "CoreData/Artist.h"
#include <QNetworkReply>
#include <QDomDocument>
#include <QPixmap>
#include <QDebug>

using namespace Core;
LastFMInfoResolver::LastFMInfoResolver(QObject *parent) : AbstractInfoResolver(parent)
{
    lastFMUsr = "321f5ce34dce204decefa79149e7f02f";
    lastFMKey =  "254c7a8847161c7b8b0a30a7440b96b3";

    manager = new QNetworkAccessManager(this);

    connect(this, SIGNAL(coverFound(QString)), this, SLOT(fetchCover(QString)));
    connect(this, SIGNAL(newRequest(QString, QString)), this, SLOT(startRequest(QString, QString)),Qt::QueuedConnection);
}

QStringList LastFMInfoResolver::getSupportedInfoTypes()
{
    QStringList list;
    list.append("org.safri.audio.album.cover");
    list.append("org.safri.audio.album.cover.hires");
    return list;
}

void LastFMInfoResolver::getInfo(QString type, DataItem *item)
{
    qDebug()<<Q_FUNC_INFO<<" Type:"<<type;
    if (DataItem::typeToString(item->getType()) == "ALBUM")
    {
        if(type == "org.safri.audio.album.cover")
        {
            Album* album = qobject_cast<Album*>(item);
            if(album)
            {
                getAlbumInfo(album, "default");
            }
        }

        if(type == "org.safri.audio.album.cover.hires")
        {
            Album* album = qobject_cast<Album*>(item);
            if(album)
            {
                getAlbumInfo(album, "hires");
            }
        }
    }
}


//1
void LastFMInfoResolver::getAlbumInfo(Core::Album *album, QString type)
{
    QString artist = album->getArtists().at(0)->getName();
    QString albumName = album->getName();
    getAlbumInfo(albumName, artist, type);
}

//2
void LastFMInfoResolver::getAlbumInfo(QString album, QString artist, QString type)
{
    QString requestString("http://ws.audioscrobbler.com/2.0/");
    QUrlQuery url(requestString+"?method=album.getinfo");
    //url.addQueryItem("method", "album.getInfo");
    url.addQueryItem("api_key", lastFMUsr);
    url.addQueryItem("artist",artist);
    url.addQueryItem("album", album);
    Q_EMIT newRequest(url.toString(), type);
}

//3
void LastFMInfoResolver::startRequest(QString url, QString type)
{
    QNetworkReply* reply = manager->get( QNetworkRequest( url ) );
    reply->setProperty("type", type);
    //qDebug()<<url;
    connect( reply, SIGNAL( finished() ), SLOT( coverRequestCallBack()));
}

//4
void LastFMInfoResolver::coverRequestCallBack()
{
    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    QString type = reply->property("type").toString();

    if ( !reply )
    {
        setError("network reply null");
        return;
    }
    if(reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError)
    {
        QDomDocument doc;
        doc.setContent(reply->readAll());
        QDomNodeList domNodeList = doc.elementsByTagName( "image" );
        if (!domNodeList.isEmpty())
        {
            if(type =="default" && !domNodeList.at(2).toElement().text().isEmpty())
            {
                Q_EMIT coverFound(domNodeList.at(2).toElement().text());
            }
            else if (type =="hires" && !domNodeList.at(3).toElement().text().isEmpty())
            {
                Q_EMIT coverFound(domNodeList.at(3).toElement().text());
            }
            else
            {
                setError("No Cover found  )= ");
            }
        }
    }
    else
    {
        setError(reply->errorString());
    }
    reply->deleteLater();
}

void LastFMInfoResolver::fetchCover(QString url)
{
    QNetworkReply* reply = manager->get(QNetworkRequest( url ));
    reply->
    connect(reply, SIGNAL(finished()),  this, SLOT(fetchCoverCallback()));
}



void LastFMInfoResolver::fetchCoverCallback()
{
    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    if ( !reply )
    {
        setError(QString(Q_FUNC_INFO).append( " no reply."));
        return;
    }

    if(reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError)
    {
        QPixmap image; //= new QPixmap();
        image.loadFromData(reply->readAll());
        setInfo(QVariant(image));
    }
    else
    {
        setError(reply->errorString());
    }
    reply->deleteLater();
}


