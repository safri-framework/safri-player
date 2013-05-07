#include "StaticPlayerHelper.h"
#include "iplaybackcontroller.h"
#include "CoreData/audio.h"
#include "icore.h"
#include "iplaylist.h"
#include <QJsonDocument>

StaticPlayerHelper::StaticPlayerHelper(){}

QJsonObject StaticPlayerHelper::getStatus()
{
    QJsonObject obj;
    QVariantMap map;
    map.insert("playlistPosition",Core::ICore::playbackController()->getPlaylist()->getCurrentMediaPosition());
    obj = QJsonObject::fromVariantMap(map);
    obj.insert("currentMedia", getMedia(Core::ICore::playbackController()->getPlaylist()->getCurrentMedia()));
    return obj;
}

QJsonObject StaticPlayerHelper::getMedia(Core::DataItem* item)
{
    QVariantMap map;
    if(item->getType() == Core::DataItem::SONG)
    {
        Core::Song* song = qobject_cast<Core::Song*>(item);
        if(song)
        {
            map.insert("type",      "org.safri.audio.song");
            map.insert("name",      song->getName());
            map.insert("artist",    song->getArtist()->getName());
            map.insert("album",     song->getAlbum()->getName());
            map.insert("genre",     song->getGenre()->getName());
            map.insert("id",        song->getID());
            map.insert("artistID",  song->getArtist()->getID());
            map.insert("albumID",   song->getAlbum()->getID());
            map.insert("genreID",   song->getGenre()->getID());
        }
    }
    else if(item->getType() == Core::DataItem::ARTIST)
    {
        Core::Artist* artist = qobject_cast<Core::Artist*>(item);
        if(artist)
        {
            map.insert("type",      "org.safri.audio.artist");
            map.insert("name",      artist->getName());
            map.insert("id",        artist->getID());
        }
    }
    else if(item->getType() == Core::DataItem::GENRE)
    {
        Core::Genre* genre = qobject_cast<Core::Genre*>(item);
        if(genre)
        {
            map.insert("type",      "org.safri.audio.genre");
            map.insert("name",      genre->getName());
            map.insert("id",        genre->getID());
        }
    }
    else if(item->getType() == Core::DataItem::ALBUM)
    {
        Core::Album* album = qobject_cast<Core::Album*>(item);
        if(album)
        {
            map.insert("type",      "org.safri.audio.album");
            map.insert("name",       album->getName());
            map.insert("id",         album->getID());
        }
    }
    return QJsonObject::fromVariantMap(map);
}
