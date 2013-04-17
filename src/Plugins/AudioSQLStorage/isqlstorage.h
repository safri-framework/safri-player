#ifndef ISQLSTORAGE_H
#define ISQLSTORAGE_H

#include <QObject>
#include <QSqlQuery>

class ISQLStorage : public QObject
{
    Q_OBJECT
    public:

        explicit ISQLStorage(QObject *parent = 0);
        virtual ~ISQLStorage();

        enum OPERATION_MODE { INVALID, READ, WRITE };

        virtual bool        open(OPERATION_MODE mode) = 0;
        virtual bool        close() = 0;
        virtual bool        abort() = 0;
        virtual QSqlQuery   createQuery() = 0;
};

#endif // ISQLSTORAGE_H
