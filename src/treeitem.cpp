#include "treeitem.h"

TreeItem::TreeItem(Playlist* playlist, QString type, QString filename, QString text, TreeItem* treeParent, QObject *parent) :
 playlist(playlist), type(type), text(text), treeParent(treeParent), childs(0), QObject(parent)
{
    //QUrl info(filename);
    //this->filename = info.toLocalFile();
this->filename = filename;

    childs = new QList<TreeItem*>;
}


TreeItem* TreeItem::getParent()
{
    return treeParent;
}

QList<TreeItem*>* TreeItem::getChilds()
{
    return childs;
}

QString TreeItem::getFilename()
{
    return filename;
}

QString TreeItem::getText()
{
    return text;
}

QString TreeItem::getType()
{
    return type;
}

Playlist* TreeItem::getPlaylist()
{
    return playlist;
}
