#include "StaticPlayerHelper.h"
#include "iplaybackcontroller.h"
#include "CoreData/song.h"
#include "icore.h"

#include "iplaylist.h"

#include <QJsonDocument>

StaticPlayerHelper::StaticPlayerHelper()
{
}



QJsonObject StaticPlayerHelper::getStatus()
{
    QJsonObject obj;
    QVariantMap map;
    map.insert("playlistPosition",Core::ICore::playbackController()->getPlaylist()->getCurrentMediaPosition());
    obj = QJsonObject::fromVariantMap(map);
    obj.insert("currentMedia", getMedia(Core::ICore::playbackController()->getPlaylist()->getCurrentMedia()));
    return obj;
}

QJsonObject StaticPlayerHelper::getMedia(Core::Media* media)
{
    Core::Song* song = qobject_cast<Core::Song*>(media);
    if(song && media->getType() == Core::Media::SONG)
    {
        QVariantMap map;
        map.insert("type","org.safri.collection.audio");
        map.insert("song", song->getName());
        map.insert("artist", song->getArtist()->getName());
        map.insert("album", song->getAlbum()->getName());
        map.insert("genre", song->getGenre()->getName());
        map.insert("songID", song->getID());
        map.insert("artistID", song->getArtist()->getID());
        map.insert("albumID", song->getAlbum()->getID());
        map.insert("genreID", song->getGenre()->getID());
        return QJsonObject::fromVariantMap(map);
    }
    return QJsonObject();
}
