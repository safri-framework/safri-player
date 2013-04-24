#ifndef INFOREQUEST_H
#define INFOREQUEST_H

#include <QObject>
#include <QVariant>
class InfoRequest : public QObject
{
    Q_OBJECT
public:
    explicit InfoRequest(QObject *parent = 0);
    void setInfoData(QVariant info);
    bool isInfoAvailable();
    QVariant getInfo();

signals:
    void infoDataAvailable();

private:
    QVariant info;
    bool infoAvailable;

public slots:


    
};

#endif // INFOREQUEST_H
