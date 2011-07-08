#ifndef DATABASECLEANER_H
#define DATABASECLEANER_H

#include <QThread>

class DatabaseCleaner : public QThread
{
    Q_OBJECT
public:
    explicit DatabaseCleaner(QObject *parent = 0);
    void run();

signals:



public slots:

};

#endif // DATABASECLEANER_H
