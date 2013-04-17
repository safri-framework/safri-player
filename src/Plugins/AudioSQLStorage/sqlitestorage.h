#ifndef SQLITESTORAGE_H
#define SQLITESTORAGE_H

#include "isqlstorage.h"
#include <QUrl>
#include <QSqlDatabase>


class SQLiteStorage : public ISQLStorage
{
    Q_OBJECT
    public:
        explicit SQLiteStorage(QUrl url, QObject *parent = 0);
        ~SQLiteStorage();

        virtual bool        open(OPERATION_MODE openMode);
        virtual bool        close();
        virtual bool        abort();
        virtual QSqlQuery   createQuery();

    private:

        QUrl url;
        OPERATION_MODE currentMode;
        QSqlDatabase database;
};

#endif // SQLITESTORAGE_H
