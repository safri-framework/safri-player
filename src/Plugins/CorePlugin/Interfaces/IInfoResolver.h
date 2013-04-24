#ifndef IINFORESOLVER_H
#define IINFORESOLVER_H
#include "../CoreSupply/InfoTypeDefinition.h"
#include <QObject>

class InfoRequest;
class DataItem;
class IInfoResolver : public QObject
{
    Q_OBJECT

public:
    explicit IInfoResolver(QObject *parent = 0);
    virtual ~IInfoResolver();
    virtual QStringList getSupportedInfoTypes() = 0;
    virtual InfoRequest* getInfoForItem(QString type, DataItem* item) = 0;

signals:
    
public slots:
    
};

#endif // IINFORESOLVER_H
