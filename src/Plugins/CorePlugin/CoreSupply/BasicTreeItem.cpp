#include "BasicTreeItem.h"

using namespace Core;

BasicTreeItem::BasicTreeItem(ITreeItem *parentItem, QObject *parent) :
    ITreeItem(parent), parentItem(parentItem)
{
}

ITreeItem *BasicTreeItem::getParent()
{
    return parentItem;
}

void BasicTreeItem::setParent(ITreeItem *sParent)
{
    parentItem = sParent;
    Q_EMIT parentChanged(parentItem);
}

int BasicTreeItem::getChildCount()
{
    return childs.size();
}

ITreeItem *BasicTreeItem::getChildAt(int index)
{
    return childs.at(index);
}

int BasicTreeItem::getIndexOfChild(ITreeItem* child)
{
    return childs.indexOf(child);
}

void BasicTreeItem::addChild(ITreeItem *child)
{
    childs.append(child);
    Q_EMIT childAdded(child);
}

void BasicTreeItem::removeChild(ITreeItem *child)
{
    childs.removeAll(child);
    Q_EMIT childRemoved(child);
}
