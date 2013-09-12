#include "DecadeItemType.h"
#include "../../CoreData/Song.h"
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
    Q_UNUSED(song)
    return 0;
}

QString DecadeItemType::getHash(Song *song)
{
    int year = song->getYear();
    year -= year % 10;
    return QString::number(year);
}


