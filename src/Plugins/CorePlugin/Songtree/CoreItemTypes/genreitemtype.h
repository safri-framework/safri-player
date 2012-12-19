#ifndef GENREITEMTYPE_H
#define GENREITEMTYPE_H

#include <QString>

#include "itreeitemtype.h"

/**
    \brief  ItemType that generates the node name for the genre of a song.

    This implementation of the ITreeItemType interface generates the node name
    for the genre of a song.
  */
class GenreItemType : public ITreeItemType
{
public:
    GenreItemType();

    QString getTypeName();
    QString getNodeName(Song* song);
    BaseDTO* getNodeDTO(Song *song);
    QString getHash(Song* song);
    QList<QAction*>* getContextMenuActions(SongTreeItem* item);
};

#endif // GENREITEMTYPE_H
