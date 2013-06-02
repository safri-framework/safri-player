#include "LastFMInfoResolver.h"
#include <QStringList>
#include "CoreData/artist.h"
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
    connect(this, SIGNAL(newRequest(QString)), this, SLOT(startRequest(QString)),Qt::QueuedConnection);
}

QStringList LastFMInfoResolver::getSupportedInfoTypes()
{
    QStringList list;
    list.append("org.safri.audio.album.cover");
    list.append("org.");
    return list;
}

void LastFMInfoResolver::getInfo(QString type, DataItem *item)
{

    if(type == "org.safri.audio.album.cover" && DataItem::typeToString(item->getType()) == "ALBUM")
    {
        Album* album = qobject_cast<Album*>(item);
        if(album)
        {
            getAlbumCover(album);
        }
    }
}

void LastFMInfoResolver::getAlbumCover(Core::Album *album)
{
    QString artist = album->getArtists().at(0)->getName();
    QString albumName = album->getName();
    getAlbumCover(albumName, artist);
}

void LastFMInfoResolver::getAlbumCover(QString album, QString artist)
{
    QString requestString("http://ws.audioscrobbler.com/2.0/");
    QUrlQuery url(requestString+"?method=album.getinfo");
    //url.addQueryItem("method", "album.getInfo");
    url.addQueryItem("api_key", lastFMUsr);
    url.addQueryItem("artist",artist);
    url.addQueryItem("album", album);
    Q_EMIT newRequest(url.toString());
}

void LastFMInfoResolver::coverRequestCallBack()
{
    qDebug()<<"REPLY";
    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    if ( !reply )
    {
        qDebug()<<"network reply null";
        return;
    }
    if(reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError)
    {
        qDebug()<<"NO ERROR";
        QDomDocument doc;
        //qDebug()<<reply->readAll();
        doc.setContent(reply->readAll());
        QDomNodeList domNodeList = doc.elementsByTagName( "image" );
        if (!domNodeList.isEmpty() && !domNodeList.at(2).toElement().text().isEmpty())
        {
            Q_EMIT coverFound(domNodeList.at(2).toElement().text());
        }
        else
        {
            Q_EMIT error("No Cover found  )= ");
            setInfo(QVariant());
        }
    }
    else
    {
        Q_EMIT error( reply->errorString());
        qDebug()<<reply->errorString();
    }
    reply->deleteLater();
}

void LastFMInfoResolver::fetchCover(QString url)
{
    QNetworkReply* reply = manager->get(QNetworkRequest( url ));
    connect(reply, SIGNAL(finished()),  this, SLOT(fetchCoverCallback()));
}

void LastFMInfoResolver::startRequest(QString url)
{
    QNetworkReply* reply = manager->get( QNetworkRequest( url ) );
    reply->setProperty("albumID", -1);
    qDebug()<<url;
    connect( reply, SIGNAL( finished() ), SLOT( coverRequestCallBack()));
}

void LastFMInfoResolver::fetchCoverCallback()
{
    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    if ( !reply )
    {
        qDebug()<<"network reply null";
        return;
    }

    QPixmap image; //= new QPixmap();
    image.loadFromData(reply->readAll());
    setInfo(QVariant(image));
}


