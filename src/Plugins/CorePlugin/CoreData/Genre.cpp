#include "Genre.h"

using namespace Core;


QList<Media *> Genre::getMedia()
{
    //TODO
    return QList<Media*>();
}

Genre::Genre(int sID, QString sName, QObject *parent) :
    DataItem(sID, sName, DataItem::GENRE, parent)
{

}

Genre::Genre(int sID, QString sName, bool temporary, QObject *parent):
    DataItem(sID, sName, DataItem::GENRE, temporary, parent)
{
}

Genre::Genre(Genre* genre, QObject *parent):
    DataItem(-1 /*TODO*/, genre->getName(), DataItem::GENRE, parent)
{

}

void Genre::addSong(Song* song)
{
    this->songs.append(song);
}

void Genre::removeSong(Song* song)
{
   this->songs.removeOne(song);
}

QList<Song*> Genre::getSongs()
{
    return this->songs;
}
