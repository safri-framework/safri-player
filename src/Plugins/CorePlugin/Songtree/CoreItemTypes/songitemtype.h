#ifndef SONGTREEITEMTYPE_H
#define SONGTREEITEMTYPE_H

#include <QString>

#include "itreeitemtype.h"
#include "song.h"

/**
    \brief  ItemType that generates the node name for the title of a song.

    This implementation of the ITreeItemType interface generates the node name
    for the title of a song.
  */
class SongItemType : public ITreeItemType
{

    public:
        SongItemType();

        QString getTypeName();
        QString getNodeName(Song* song);
        BaseDTO* getNodeDTO(Song *song);
        QString getHash(Song* song);
        QList<QAction*>* getContextMenuActions(SongTreeItem* item);
};

#endif // SONGTREEITEMTYPE_H
