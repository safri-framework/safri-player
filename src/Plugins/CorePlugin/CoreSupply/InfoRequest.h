#ifndef INFOREQUEST_H
#define INFOREQUEST_H

#include <QObject>
#include <QVariant>

class Item;
class InfoRequest : public QObject
{
    Q_OBJECT
public:
    explicit InfoRequest(Item* relatedItem, QObject *parent = 0);
    void setInfoData(QVariant info);
    bool isInfoAvailable();
    Item* getRelatedItem();
    QVariant getInfo();

signals:
    void infoDataAvailable();

private:
    QVariant info;
    Item* relatedItem;
    bool infoAvailable;

public slots:


    
};

#endif // INFOREQUEST_H
