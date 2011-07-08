#include "basedto.h"

BaseDTO::BaseDTO(int sID, QString sText, DTO_TYPE sType, QObject *parent) :
    QObject(parent), childs(0), parentDTO(0), type(sType), id(sID), text(sText)
{
    childs = new QList<BaseDTO*>();
}


QList<BaseDTO*> *BaseDTO::getChildren()
{
    return childs;
}

BaseDTO *BaseDTO::getParentDTO()
{
    return parentDTO;
}

void BaseDTO::setChildren(QList<BaseDTO*> *sChilds)
{
    childs = sChilds;
}

void BaseDTO::setParent(BaseDTO* sParent)
{
    parentDTO = sParent;
}

BaseDTO::DTO_TYPE BaseDTO::getType()
{
    return type;
}

BaseDTO::DTO_TYPE BaseDTO::getParentType()
{
    if (parentDTO == 0)
    {
        return NONE;
    }
    else
    {
        return parentDTO->getType();
    }
}

BaseDTO::DTO_TYPE BaseDTO::getChildrenType()
{
    if (childs == 0)
    {
        return NONE;
    }
    else if (childs->length() >= 1)
    {
        return childs[0].at(0)->getType();
    }
    else
    {
        return NONE;
    }

}

int BaseDTO::getID()
{
    return id;
}

QString BaseDTO::getText() const
{
    return text;
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

bool BaseDTO::sortAtoZ( const BaseDTO* dto1, const BaseDTO* dto2)
{

    return dto1->getText().toLower() < dto2->getText().toLower();
}
