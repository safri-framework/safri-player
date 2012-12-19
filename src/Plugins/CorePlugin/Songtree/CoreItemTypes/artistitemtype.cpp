#include "artistitemtype.h"

ArtistItemType::ArtistItemType()
{
}



QString ArtistItemType::getTypeName()
{
    return "ArtistType";
}


QString ArtistItemType::getNodeName(Song* song)
{

return song->getInterpret()->getName();

}


BaseDTO* ArtistItemType::getNodeDTO(Song *song)
{
    return song->getInterpret();

}

QString ArtistItemType::getHash(Song *song)
{
    Artist *artist = song->getInterpret();
    return QString::number(artist->getID()) + artist->getName();
}

QList<QAction *> *ArtistItemType::getContextMenuActions(SongTreeItem *item)
{
    return 0;
}
