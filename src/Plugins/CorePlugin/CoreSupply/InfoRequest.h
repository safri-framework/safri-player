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
        void setError(QString errorString);
        bool isInfoAvailable();
        Core::DataItem* getRelatedItem();
        QVariant getInfo();
        QString getRequestType();
        QString getErrorString();

    signals:
        void infoDataAvailable();
        void error();

    private:
        QVariant info;
        Core::DataItem* relatedItem;
        bool infoAvailable;
        QString requestType;
        QString errorString;

    };
}

#endif // INFOREQUEST_H
