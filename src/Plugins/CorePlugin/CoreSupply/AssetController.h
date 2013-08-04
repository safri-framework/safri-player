#ifndef ASSETCONTROLLER_H
#define ASSETCONTROLLER_H

#include "CorePlugin_global.h"
#include <QObject>
#include <QMap>
#include "../Interfaces/IAssetService.h"
#include "CoreData/dataitem.h"

namespace Controller
{
    class COREPLUGINSHARED_EXPORT AssetController : public QObject
    {
        Q_OBJECT
    public:
        explicit AssetController(QObject *parent = 0);
        QVariant getAsset(QString serviceName, Core::DataItem* item);

    signals:

    public slots:

    private slots:
        void objectAdded(QObject* object);
    private:
        void addService(Core::IAssetService* service);
        QMap<Core::DataItem::DATA_ITEM_TYPE, QMap<QString, Core::IAssetService*>*>  assetServices;

    };
}
#endif // ASSETCONTROLLER_H
