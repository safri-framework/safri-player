#ifndef DATATABLESAVER_H
#define DATATABLESAVER_H

#include <QThread>
#include "databasedao.h"

class DataTableSaver : public QThread
{
    Q_OBJECT
public:
    explicit DataTableSaver(int flags, QObject *parent = 0);
    void run();

signals:

    void songSaved(int);
    void setRange(int, int);
    void setProgressBarText(QString text);
    void showProgressBar();
    void hideProgressBar();

private:
    QList<DatabaseDAO::ColumnData*>* columnList;
    int flags;


public slots:

};

#endif // DATATABLESAVER_H
