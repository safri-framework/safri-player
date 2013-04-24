#ifndef ABSTRACTINFORESOLVER_H
#define ABSTRACTINFORESOLVER_H

#include <QMutex>
#include "../Interfaces/IInfoResolver.h"

class AbstractInfoResolver : public IInfoResolver
{
    Q_OBJECT

public:
    explicit AbstractInfoResolver(QObject *parent = 0);

    virtual QStringList                 getSupportedInfoTypes() = 0;
    virtual InfoRequest*                getInfoForItem(QString type, DataItem* item);
    virtual void                        getInfo(QString type, DataItem* item) = 0;
    void                                setInfo(QVariant info);
private:
    void                                insertInFifo(InfoRequest* request);
    InfoRequest*                        getNextRequest();
    bool                                hasRequest();
    bool running;
    QList<InfoRequest*> requestList;
    QMutex  fifoMutex;
    InfoRequest* currentRequest;
};

#endif // ABSTRACTINFORESOLVER_H