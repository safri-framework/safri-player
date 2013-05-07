#ifndef INFOREQUEST_H
#define INFOREQUEST_H
#include "CoreData/dataitem.h"
#include "../CorePlugin_global.h"
#include <QObject>
#include <QVariant>


namespace Core
{
    class COREPLUGINSHARED_EXPORT InfoRequest : public QObject
    {
        Q_OBJECT
    public:
        explicit InfoRequest(QString requestType, Core::DataItem* relatedItem, QObject *parent = 0);
        void setInfoData(QVariant info);
        bool isInfoAvailable();
        Core::DataItem* getRelatedItem();
        QVariant getInfo();
        QString getRequestType();

    signals:
        void infoDataAvailable();

    private:
        QVariant info;
        Core::DataItem* relatedItem;
        bool infoAvailable;
        QString requestType;

    };
}

#endif // INFOREQUEST_H
