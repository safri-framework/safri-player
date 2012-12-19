#ifndef DECADETREEITEMTYPE_H
#define DECADETREEITEMTYPE_H

#include <QString>

#include "itreeitemtype.h"

/**
    \brief  ItemType that generates the node name for the decade of a song.

    This implementation of the ITreeItemType interface generates the node name
    for the decade of a song. As there is no essential BaseDTO for decades the
    getNodeDTO function only returns 0.
  */
class DecadeItemType : public ITreeItemType
{
    public:
        DecadeItemType();
        QString getTypeName();
        QString getNodeName(Song* song);
        BaseDTO* getNodeDTO(Song *song);
        QString getHash(Song* song);
        QList<QAction*>* getContextMenuActions(SongTreeItem* item);
};

#endif // DECADETREEITEMTYPE_H
