#include "decadeitemtype.h"
#include "../../CoreData/song.h"
#include <QDebug>

using namespace Core;

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


DataItem* DecadeItemType::getNodeDataItem(Song *song)
{
    return 0;
}

QString DecadeItemType::getHash(Song *song)
{
    int year = song->getYear();
    year -= year % 10;
    return QString::number(year);
}


