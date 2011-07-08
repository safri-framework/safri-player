#include "dtomapentry.h"

DTOMapEntry::DTOMapEntry(QObject *parent) : children(0), dto(0), valid(false)
{

}

DTOMapEntry::DTOMapEntry(QMap<int, DTOMapEntry*> *sChildren, BaseDTO *sDTO, QObject *parent) :
    QObject(parent), children(sChildren), dto(sDTO), valid(true)
{

}

bool DTOMapEntry::isValid() const
{
    return valid;
}

QMap<int, DTOMapEntry*>* DTOMapEntry::getChildren() const
{
    return children;
}

BaseDTO* DTOMapEntry::getDTO() const
{
    return dto;
}
