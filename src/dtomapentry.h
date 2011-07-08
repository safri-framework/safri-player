#ifndef DTOMAPENTRY_H
#define DTOMAPENTRY_H

#include <QObject>
#include <QMap>
#include "basedto.h"

class DTOMapEntry : public QObject
{
        Q_OBJECT
    public:
        explicit DTOMapEntry(QObject *parent = 0);
        explicit DTOMapEntry(QMap<int, DTOMapEntry*> *sChildren, BaseDTO *sDTO, QObject *parent = 0);


        QMap<int, DTOMapEntry*>* getChildren() const;
        BaseDTO* getDTO() const;

        bool isValid() const;

    signals:

    public slots:

    private:

        QMap<int, DTOMapEntry*> *children;
        BaseDTO *dto;

        bool valid;


};

#endif // DTOMAPENTRY_H
