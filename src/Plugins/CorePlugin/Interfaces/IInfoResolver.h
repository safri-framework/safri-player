#ifndef IINFORESOLVER_H
#define IINFORESOLVER_H
#include "../CoreSupply/InfoTypeDefinition.h"
#include <QObject>

class InfoRequest;
class Item;
class IInfoResolver : public QObject
{
    Q_OBJECT

public:
    explicit IInfoResolver(QObject *parent = 0);
    virtual ~IInfoResolver();
    virtual QStringList getSupportedInfoTypes() = 0;
    virtual InfoRequest* getInfoForItem(Core::InfoType type, Item* DataItem) = 0;

signals:
    
public slots:
    
};

#endif // IINFORESOLVER_H
