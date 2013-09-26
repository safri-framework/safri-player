#ifndef MPCTESTTEST_H
#define MPCTESTTEST_H

#include <QObject>
#include <QTcpSocket>
#include "Interfaces/IAudioCollection.h"

class MPCInserter : public QObject
{
    Q_OBJECT
public:
    explicit MPCInserter(QObject *parent = 0);
    
signals:
    
public slots:

private slots:
    void readTcpData();
    void test();

private:
    QTcpSocket* _pSocket;
    Core::IAudioCollection* _audioCollection;
    
};

#endif // MPCTESTTEST_H
