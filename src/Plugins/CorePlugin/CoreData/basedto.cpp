#include "basedto.h"

#include <QDebug>

using namespace Core;

BaseDTO::BaseDTO(int sID, QString sName, DTO_TYPE sType, QObject *parent) :
    QObject(parent), type(sType), id(sID), name(sName), temporary(false)
{

}


BaseDTO::BaseDTO(int sID, QString sName, DTO_TYPE sType, bool temporary, QObject *parent) :
    QObject(parent), type(sType), id(sID), name(sName), temporary(temporary)
{

}

BaseDTO::~BaseDTO()
{
    qDebug() << "~BaseDTO";
}

BaseDTO::DTO_TYPE BaseDTO::getType() const
{
    return type;
}

int BaseDTO::getID() const
{
    return id;
}

QString BaseDTO::getName() const
{
    return name;
}

bool BaseDTO::getTemporary() const
{
    return temporary;
}

void BaseDTO::setName(QString sName)
{
    name = sName;
}

void BaseDTO::setID(int sID)
{
    id = sID;
}

QString BaseDTO::typeToString(DTO_TYPE type)
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
    }

    return "";
}


BaseDTO::DTO_TYPE BaseDTO::stringToType(QString type)
{
    if (type == "NONE")
        return BaseDTO::NONE;
    if (type == "GENRE")
        return BaseDTO::GENRE;
    if (type == "ALBUM")
        return BaseDTO::ALBUM;
    if (type == "ARTIST")
        return BaseDTO::ARTIST;
    if (type == "SONG")
        return BaseDTO::SONG;
    if (type == "CD")
        return BaseDTO::CD;
    if (type == "TAG")
        return BaseDTO::TAG;
    if (type == "DECADE")
        return BaseDTO::DECADE;
    if (type == "YEAR")
        return BaseDTO::YEAR;

    return BaseDTO::NONE;
}
