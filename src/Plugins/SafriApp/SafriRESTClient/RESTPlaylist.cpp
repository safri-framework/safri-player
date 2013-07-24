#include "RESTPlaylist.h"

#include "RESTClient.h"
#include "RESTActions.h"
#include "CoreData/mediainfocontainer.h"

#include <QDebug>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QRegExp>

#include <QEventLoop>

using namespace SafriRESTClient;

RESTPlaylist::RESTPlaylist(RESTClient *restClient, QObject *parent) :
    QObject(parent), client(restClient), songList(), currentMediaPosition(-1), m_valid(false), versionCheckTimer(new QTimer(this)), displayedPlaylistVersion(-1)
{
   // requestCurrentPlaylist();
    connect(versionCheckTimer, SIGNAL(timeout()), this, SLOT(versionTimeoutSlot()));
    versionCheckTimer->setInterval(VERSION_TIMER_INTERVAL);
    versionCheckTimer->start();
}

RESTPlaylist::~RESTPlaylist()
{
    qDebug() << "~RESTPlaylist: stopping versionCheckTimer";
    versionCheckTimer->stop();
}

bool RESTPlaylist::isCurrentMedia(int index)
{
}

void RESTPlaylist::moveMedia(int fromPosition, int toPosition)
{
    QString moveRequest = RESTAction::PLAYLIST_MOVE_MEDIA;
    moveRequest.replace(QRegExp("%%FROMPOS%%"), QString::number(fromPosition));
    moveRequest.replace(QRegExp("%%TOPOS%%"), QString::number(toPosition));

    displayedPlaylistVersion++;
    client->sendRequest(moveRequest);


    songList.move(fromPosition, toPosition);

    Q_EMIT mediaMoved(fromPosition, toPosition);
}

void RESTPlaylist::playPlaylistIndex(int index)
{
    QString playRequest = RESTAction::PLAYLIST_PLAY_INDEX;
    playRequest.replace(QRegExp("%%PLAYPOS%%"), QString::number(index));
    client->sendRequest(playRequest);
    qDebug()<<"PLAY";
}

int RESTPlaylist::getSize()
{
    return songList.size();
}

int RESTPlaylist::getCurrentMediaPosition()
{
    return currentMediaPosition;
}

void RESTPlaylist::insertNodeAtPosition(int node, int position)
{
}

bool RESTPlaylist::isValid()
{
    return m_valid;
}

void RESTPlaylist::removeIndexFromPlaylist(int index)
{
    QString request = RESTAction::PLAYLIST_DELETE_INDEX;
    request.replace(QRegExp("%%DELETEPOS%%"), QString::number(index));
    delete songList.at(index);
    songList.removeAt(index);
    Q_EMIT mediaDeleted(index);
    displayedPlaylistVersion++;
    client->sendRequest(request) ;
}

void RESTPlaylist::setShuffle(bool enabled)
{
    QString request = RESTAction::PLAYLIST_SET_SHUFFLE;
    if(enabled)
        request.replace(QRegExp("%%VALUE%%"), "true");
    else
        request.replace(QRegExp("%%VALUE%%"), "false");
    client->sendRequest(request);

}

Core::MediaInfoContainer *RESTPlaylist::getMediaInfoAt(int position)
{
    return songList.at(position);
}

void RESTPlaylist::getCurrentPlaylistReply()
{
    Q_EMIT beginResetModel();
    for(int i = 0; i < songList.size();i++)
    {
        delete songList.at(i);
    }
    songList.clear();

    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    if ( !reply )
    {
        qDebug() << "network reply null";
    }
    else
    {
        if(reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError)
        {
            QJsonDocument jsonDoc = QJsonDocument::fromJson( reply->readAll() );
            QJsonArray jsonItemArray = jsonDoc.object().value("playingPlaylist").toArray();
            QJsonObject jsonPlaylistEntry;
            QVariantMap playlistEntryMap;
            Core::MediaInfoContainer* newInfoContainer;

            int entryCount = jsonItemArray.size();

            for (int i = 0; i < entryCount; i++)
            {
                jsonPlaylistEntry = jsonItemArray.at(i).toObject();
                playlistEntryMap = jsonPlaylistEntry.toVariantMap();

                newInfoContainer = new Core::MediaInfoContainer();

                newInfoContainer->setMediaInfo(Core::InfoAlbum, playlistEntryMap.value("album"));
                newInfoContainer->setMediaInfo(Core::InfoGenre, playlistEntryMap.value("genre"));
                newInfoContainer->setMediaInfo(Core::InfoTitle, playlistEntryMap.value("name"));
                newInfoContainer->setMediaInfo(Core::InfoArtist, playlistEntryMap.value("artist"));

                newInfoContainer->setProperty("albumID", playlistEntryMap.value("albumID"));
                newInfoContainer->setProperty("artistID", playlistEntryMap.value("artistID"));
                newInfoContainer->setProperty("songID", playlistEntryMap.value("songID"));
                newInfoContainer->setProperty("genreID", playlistEntryMap.value("genreID"));

                songList.append(newInfoContainer);
            }
        }

        m_valid = true;
        Q_EMIT valid(true);
        Q_EMIT endResetModel();
    }
}

void RESTPlaylist::requestCurrentPlaylist()
{
    QNetworkReply *reply =client->sendRequest(RESTAction::PLAYLIST_GET_CURRENT, this, SLOT(getCurrentPlaylistReply()));

    // start an event loop to wait synchronously for the REST request to finish
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

void RESTPlaylist::setCurrentMediaPosition(int pos)
{
    if(pos!=currentMediaPosition)
    {
        int oldIndex = currentMediaPosition;
        currentMediaPosition = pos;
        Q_EMIT currentMediaPositionChanged(oldIndex, currentMediaPosition);
    }
}

void RESTPlaylist::versionTimeoutSlot()
{
    //timer triggered request to check if our Playlist is up to date...
    QNetworkReply *reply =client->sendRequest(RESTAction::PLAYLIST_GET_VERSION, this, SLOT(comparePlaylistVersion()));
}

void RESTPlaylist::comparePlaylistVersion()
{
    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    if ( !reply )
    {
        qDebug() << "network reply null";
    }
    else
    {
        if(reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::UnknownContentError)
        {
            QJsonDocument jsonDoc = QJsonDocument::fromJson( reply->readAll() );
            double  version = jsonDoc.object().value("currentVersionID").toDouble(-2);
            setCurrentMediaPosition(jsonDoc.object().value("currentPlayingSongIndex").toDouble(-2));
            if(version > displayedPlaylistVersion)
            {
                qDebug()<<"TRIGGER UPDATE   current"<<displayedPlaylistVersion<<"   server:"<<version;
                displayedPlaylistVersion = version;
                requestCurrentPlaylist();
            }
            else
            {

            }
        }
    }
}
