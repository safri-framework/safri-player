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
    QObject(parent), client(restClient), songList(), currentMediaPosition(-1), m_valid(false)
{
    requestCurrentPlaylist();
}

bool RESTPlaylist::isCurrentMedia(int index)
{
}

void RESTPlaylist::moveMedia(int fromPosition, int toPosition)
{
    QString moveRequest = RESTAction::PLAYLIST_MOVE_MEDIA;
    moveRequest.replace(QRegExp("%%FROMPOS%%"), QString::number(fromPosition));
    moveRequest.replace(QRegExp("%%TOPOS%%"), QString::number(toPosition));

    client->sendRequest(moveRequest);

    songList.move(fromPosition, toPosition);

    Q_EMIT mediaMoved(fromPosition, toPosition);
}

int RESTPlaylist::getSize()
{
    return songList.size();
}

int RESTPlaylist::getCurrentMediaPosition()
{
}

void RESTPlaylist::insertNodeAtPosition(int node, int position)
{
}

bool RESTPlaylist::isValid()
{
    return m_valid;
}

Core::MediaInfoContainer *RESTPlaylist::getMediaInfoAt(int position)
{
    return songList.at(position);
}

void RESTPlaylist::getCurrentPlaylistReply()
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
