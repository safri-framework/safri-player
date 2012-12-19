#ifndef TRACKSONGITEMTYPE_H
#define TRACKSONGITEMTYPE_H

#include "itreeitemtype.h"

/**
    \brief  ItemType that generates the node name for the title of a song
            with the leading track number.

    This implementation of the ITreeItemType interface generates the node name
    for the title of a song with the leading track number.
  */
class TrackSongItemType : public ITreeItemType
{
    public:

        TrackSongItemType();

        QString getTypeName();
        QString getNodeName(Song* song);
        BaseDTO* getNodeDTO(Song *song);
        QString getHash(Song* song);
        QList<QAction*>* getContextMenuActions(SongTreeItem* item);
};

#endif // TRACKSONGITEMTYPE_H
