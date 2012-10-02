#include "genre.h"

using namespace Core;

QMap<QString, Genre*> Genre::genresByName;
QMap<int, Genre*> Genre::genresByID;
int Genre::latestID = 0;

Genre* Genre::getByName(QString name)
{
    return genresByName.value(name);
}

QList<Genre *> Genre::getAll()
{
    return genresByID.values();
}

Genre* Genre::getByID(int id)
{
    return genresByID.value(id);
}

void Genre::add(Genre* genre)
{
    genresByName.insert(genre->getName(), genre);
    genresByID.insert(genre->getID(), genre);
}

void Genre::remove(Genre* genre)
{
    genresByName.remove(genre->getName());
    genresByID.remove(genre->getID());
}

int Genre::createNewID()
{
    return ++latestID;
}


Genre::Genre(int sID, QString sName, QObject *parent) :
    BaseDTO(sID, sName, BaseDTO::GENRE, parent)
{

}

Genre::Genre(int sID, QString sName, bool temporary, QObject *parent):
    BaseDTO(sID, sName, BaseDTO::GENRE, temporary, parent)
{
}

Genre::Genre(Genre* genre, QObject *parent):
    BaseDTO(createNewID(), genre->getName(), BaseDTO::GENRE, parent)
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
