#include "decadeitemtype.h"
#include <QDebug>

DecadeItemType::DecadeItemType()
{

}

QString DecadeItemType::getTypeName()
{
    return "DecadeType";
}

QString DecadeItemType::getNodeName(Song* song)
{
    int year = song->getYear();
    year -= year % 10;
    return QString::number(year); //todo
}


BaseDTO* DecadeItemType::getNodeDTO(Song *song)
{
    return 0;
}

QString DecadeItemType::getHash(Song *song)
{
    int year = song->getYear();
    year -= year % 10;
    return QString::number(year);
}

QList<QAction *> *DecadeItemType::getContextMenuActions(SongTreeItem *item)
{
    return 0;
}
