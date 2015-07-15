#include "RESTSong.h"

using namespace SafriRESTClient;



RESTSong::RESTSong(QJsonObject jsonObject, QObject *parent)
    : Song("audio/mpeg", jsonObject.value("songID").toString().toInt(), jsonObject.value("name").toString(), 0 /* YEAR */, parent)
{
    this->interpret = new Core::Artist(jsonObject.value("artistID").toString().toInt(), jsonObject.value("artist").toString() , this );
    this->genre = new Core::Genre(jsonObject.value("genreID").toString().toInt(), jsonObject.value("genre").toString(), this);
    this->album = new Core::Album(jsonObject.value("albumID").toString().toInt(), jsonObject.value("album").toString(), this);
}
