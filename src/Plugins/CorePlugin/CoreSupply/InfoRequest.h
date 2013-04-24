#ifndef INFOREQUEST_H
#define INFOREQUEST_H

#include <QObject>
#include <QVariant>

class DataItem;
class InfoRequest : public QObject
{
    Q_OBJECT
public:
    explicit InfoRequest(DataItem* relatedItem, QObject *parent = 0);
    void setInfoData(QVariant info);
    bool isInfoAvailable();
    DataItem* getRelatedItem();
    QVariant getInfo();

signals:
    void infoDataAvailable();

private:
    QVariant info;
    DataItem* relatedItem;
    bool infoAvailable;

public slots:


    
};

#endif // INFOREQUEST_H
