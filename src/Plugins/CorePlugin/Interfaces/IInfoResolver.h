#ifndef IINFORESOLVER_H
#define IINFORESOLVER_H
#include "../CoreSupply/InfoTypeDefinition.h"
#include <QObject>
#include "CoreData/DataItem.h"
#include "../CorePlugin_global.h"



namespace Core
{
    class InfoRequest;

    class COREPLUGINSHARED_EXPORT IInfoResolver : public QObject
    {
        Q_OBJECT

    public:
        explicit IInfoResolver(QObject *parent = 0);
        virtual ~IInfoResolver();
        virtual QStringList getSupportedInfoTypes() = 0;
        virtual InfoRequest* getInfoForItem(QString type, Core::DataItem* item) = 0;

    };
}
#endif // IINFORESOLVER_H
