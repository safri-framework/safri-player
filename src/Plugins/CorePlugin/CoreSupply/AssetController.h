#ifndef ASSETCONTROLLER_H
#define ASSETCONTROLLER_H

#include <QObject>
#include <QMap>
#include "../Interfaces/IAssetService.h"

namespace Controller
{
    class AssetController : public QObject
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
        QMap<QString, Core::IAssetService*>  assetServices;

    };
}
#endif // ASSETCONTROLLER_H
