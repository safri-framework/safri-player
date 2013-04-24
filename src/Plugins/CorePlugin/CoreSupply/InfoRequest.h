#ifndef INFOREQUEST_H
#define INFOREQUEST_H

#include <QObject>
#include <QVariant>

class DataItem;
class InfoRequest : public QObject
{
    Q_OBJECT
public:
    explicit InfoRequest(QString requestType, DataItem* relatedItem, QObject *parent = 0);
    void setInfoData(QVariant info);
    bool isInfoAvailable();
    DataItem* getRelatedItem();
    QVariant getInfo();
    QString getRequestType();

signals:
    void infoDataAvailable();

private:
    QVariant info;
    DataItem* relatedItem;
    bool infoAvailable;
    QString requestType;

public slots:


    
};

#endif // INFOREQUEST_H
