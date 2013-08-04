#include "dataitem.h"

#include <QDebug>

using namespace Core;

DataItem::DataItem(int sID, QString sName, DATA_ITEM_TYPE sType, QObject *parent) :
    Item(parent), type(sType), id(sID), name(sName), temporary(false), mediaCollection(0)
{

}


DataItem::DataItem(int sID, QString sName, DATA_ITEM_TYPE sType, bool temporary, QObject *parent) :
    Item(parent), type(sType), id(sID), name(sName), temporary(temporary), mediaCollection(0)
{

}

DataItem::~DataItem()
{
    qDebug() << "~Item";
}

DataItem::DATA_ITEM_TYPE DataItem::getType() const
{
    return type;
}

int DataItem::getID() const
{
    return id;
}

QString DataItem::getName() const
{
    return name;
}

bool DataItem::isTemporary() const
{
    return temporary;
}

void DataItem::setName(QString sName)
{
    name = sName;
}

void DataItem::setID(int sID)
{
    id = sID;
}

QString DataItem::typeToString(DATA_ITEM_TYPE type)
{

    switch (type)
    {
        case NONE:
            return "NONE";
            break;

        case GENRE:
            return "GENRE";
            break;

        case ALBUM:
            return "ALBUM";
            break;

        case ARTIST:
            return "ARTIST";
            break;

        case SONG:
            return "SONG";
            break;

        case CD:
            return "CD";
            break;

        case TAG:
            return "TAG";
            break;

        case DECADE:
            return "DECADE";
            break;

        case YEAR:
            return "YEAR";
            break;

        default:
            return "";
            break;
    }

    return "";
}


DataItem::DATA_ITEM_TYPE DataItem::stringToType(QString type)
{
    if (type == "NONE")
        return DataItem::NONE;
    if (type == "GENRE")
        return DataItem::GENRE;
    if (type == "ALBUM")
        return DataItem::ALBUM;
    if (type == "ARTIST")
        return DataItem::ARTIST;
    if (type == "SONG")
        return DataItem::SONG;
    if (type == "CD")
        return DataItem::CD;
    if (type == "TAG")
        return DataItem::TAG;
    if (type == "DECADE")
        return DataItem::DECADE;
    if (type == "YEAR")
        return DataItem::YEAR;

    return DataItem::NONE;
}

IMediaCollection *DataItem::getMediaCollection()
{
    return mediaCollection;
}

void DataItem::setMediaCollection(IMediaCollection *sMediaCollection)
{
    mediaCollection = sMediaCollection;
}
