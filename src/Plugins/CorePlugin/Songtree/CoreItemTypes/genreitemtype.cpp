#include "genreitemtype.h"

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


BaseDTO* GenreItemType::getNodeDTO(Song *song)
{
    return song->getGenre();

}

QString GenreItemType::getHash(Song *song)
{
    Genre *genre = song->getGenre();
    return QString::number(genre->getID()) + genre->getName();
}






QList<QAction *> *GenreItemType::getContextMenuActions(SongTreeItem *item)
{
    return 0;
}
