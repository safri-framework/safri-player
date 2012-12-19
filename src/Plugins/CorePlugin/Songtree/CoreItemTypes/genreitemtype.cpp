#include "genreitemtype.h"
#include "../../CoreData/song.h"
using namespace Core;

GenreItemType::GenreItemType()
{
}


QString GenreItemType::getTypeName()
{
    return "GenreType";
}


QString GenreItemType::getNodeName(Song* song)
{
    return song->getGenre()->getName();
}


DataItem* GenreItemType::getNodeDataItem(Song *song)
{
    return song->getGenre();

}

QString GenreItemType::getHash(Song *song)
{
    Genre *genre = song->getGenre();
    return QString::number(genre->getID()) + genre->getName();
}







