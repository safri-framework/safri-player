#ifndef IASSETSERVICE_H
#define IASSETSERVICE_H

#include <QObject>
#include <QVariant>
#include "../CorePlugin_global.h"
#include "../CoreData/dataitem.h"

namespace Core
{
    class COREPLUGINSHARED_EXPORT IAssetService : public QObject
    {
        Q_OBJECT

    public:
        explicit IAssetService(QObject *parent = 0);
        virtual QVariant getAsset(Core::DataItem* item) = 0;
        virtual QString getName() = 0;
        virtual DataItem::DATA_ITEM_TYPE getAssetType();
    };
}

#endif // IASSETSERVICE_H
