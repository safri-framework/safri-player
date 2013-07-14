#include "JSONSerializer.h"
#include "iplaybackcontroller.h"
#include "CoreData/audio.h"
#include "icore.h"
#include "iplaylist.h"
#include "Interfaces/IMediaCollection.h"
#include <QJsonDocument>
#include <QDebug>
JSONSerializer::JSONSerializer(){}

QJsonObject JSONSerializer::getStatus()
{
    QJsonObject obj;
    QVariantMap map;
    Core::IPlaybackController* playbackController = Core::ICore::playbackController();
    QSharedPointer<Core::IPlaylist> playlist = playbackController->getPlaylist();
    if(playlist.isNull())
    {
        map.insert("playlistInstalled", false);
        map.insert("success", true);

        obj = QJsonObject::fromVariantMap(map);
    }
    else
    {
        map.insert("playlistInstalled", true);

        map.insert("playlistPosition",playlist->getCurrentMediaPosition());
        map.insert("success", true);
        map.insert("currentTime", playbackController->getCurrentTime());
        map.insert("volume", playbackController->getVolume());
        map.insert("mediaTotalTime", playbackController->getMediaTotalTime());

        obj = QJsonObject::fromVariantMap(map);

        obj.insert("currentMedia", getMedia(Core::ICore::playbackController()->getPlaylist()->getCurrentMedia()));
    }

    return obj;
}

QJsonObject JSONSerializer::getMedia(Core::DataItem* item)
{
    if (!item)
    {
        QVariantMap map;
        map.insert("failed", true);

        return QJsonObject::fromVariantMap(map);
    }

    QVariantMap map;
    if(item->getType() == Core::DataItem::SONG)
    {
        Core::Song* song = qobject_cast<Core::Song*>(item);
        if(song)
        {
            map.insert("type",          "org.safri.audio.song");
            map.insert("name",          song->getName());
            map.insert("artist",        song->getArtist()->getName());
            map.insert("album",         song->getAlbum()->getName());
            map.insert("genre",         song->getGenre()->getName());
            map.insert("collection",    song->getMediaCollection()->getHash());
            map.insert("songID",        song->getID());
            map.insert("artistID",      song->getArtist()->getID());
            map.insert("albumID",       song->getAlbum()->getID());
            map.insert("genreID",       song->getGenre()->getID());
        }
    }
    else if(item->getType() == Core::DataItem::ARTIST)
    {
        Core::Artist* artist = qobject_cast<Core::Artist*>(item);
        if(artist)
        {
            map.insert("type",          "org.safri.audio.artist");
            map.insert("name",          artist->getName());
            map.insert("id",            artist->getID());
            map.insert("collection",    artist->getMediaCollection()->getHash());
        }
    }
    else if(item->getType() == Core::DataItem::GENRE)
    {
        Core::Genre* genre = qobject_cast<Core::Genre*>(item);
        if(genre)
        {
            map.insert("type",          "org.safri.audio.genre");
            map.insert("name",          genre->getName());
            map.insert("id",            genre->getID());
            map.insert("collection",    genre->getMediaCollection()->getHash());
        }
    }
    else if(item->getType() == Core::DataItem::ALBUM)
    {
        Core::Album* album = qobject_cast<Core::Album*>(item);
        if(album)
        {
            map.insert("type",          "org.safri.audio.album");
            map.insert("name",          album->getName());
            map.insert("id",            album->getID());
            map.insert("collection",    album->getMediaCollection()->getHash());
        }
    }
    return QJsonObject::fromVariantMap(map);
}

QJsonObject JSONSerializer::generateErrorObject(QString errorMsg, QString function, bool ok)
{
    QVariantMap map;
    map.insert("error", errorMsg);
    map.insert("function", function);
    map.insert("success", ok);
    QJsonObject obj;
    obj = QJsonObject::fromVariantMap(map);
    return obj;
}

QJsonObject JSONSerializer::getSongTreeItemForJsTree(Core::SongTreeItem *item, int id)
{
    QVariantMap map;
    QJsonObject obj;

    if(item)
    {
        Core::DataItem* data = 0;
        data = item->getDataItemPtr();

        map.insert("treeItemId", id);
        map.insert("isLeaf", (item->getNumberOfChilds() == 0));
        map.insert("numberOfChilds", item->getNumberOfChilds());
        map.insert("text", item->getName());
        map.insert("type", item->getTypeName());
        obj = QJsonObject::fromVariantMap(map);
        if(data)
            obj.insert("dataItem",getMedia(data));
    }
    return obj;
}
