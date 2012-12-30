#include "songtree.h"
#include "songtreeitem.h"
#include <qDebug>
using namespace Core;

#include <QDebug>

SongTree::SongTree(QList<Song*> songs, QList<ITreeItemType*>* hierarchy)
{
    this->dirty = false;
    this->hierarchy = hierarchy;
    rootNode = new SongTreeItem(hierarchy, this, this);

    //for (int i = 0;  i < songs.size(); i++)
    qDebug()<<"a"<<songs.size();

    for (int i = 0;  i < songs.size(); i++)
    {
        qDebug()<<i;
        rootNode->addSong(songs.at(i));
    }
}

void SongTree::print()
{
    rootNode->print();
}

const SongTreeItem* SongTree::getRootNode() const
{
    return rootNode;
}

bool SongTree::isDirty()
{
    return this->dirty;
}

void SongTree::addSong(Song *song)
{
    rootNode->addSong(song);
}

void SongTree::emitBeginMoveItem(SongTreeItem *srcParent, int srcRow, SongTreeItem *destParent, int destRow)
{
    dirty = true;
    Q_EMIT beginMoveItem(srcParent, srcRow, destParent, destRow);
}

void SongTree::emitEndMoveItem(SongTreeItem *destParent)
{
    Q_EMIT endMoveItem(destParent);
}

void SongTree::emitBeginInsertItem(SongTreeItem *parent, int row)
{
    //dirty = true;
    Q_EMIT beginInsertItem(parent, row);
}

void SongTree::emitEndInsertItem()
{
    Q_EMIT endInsertItem();
}

void SongTree::emitBeginRemoveItem(SongTreeItem *parent, int row)
{
    Q_EMIT beginRemoveItem(parent, row);
}

void SongTree::emitEndRemoveItem()
{
    Q_EMIT endRemoveItem();
}

void SongTree::move(SongTreeItem *source, SongTreeItem *destination)
{
    source->moveToParent(destination);
}

void SongTree::changesSaved()
{
    dirty = false;
}
