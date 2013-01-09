#ifndef COLLECTIONCONTROLLER_H
#define COLLECTIONCONTROLLER_H

#include "../Plugins/CorePlugin/Interfaces/ICollectionController.h"
#include <QMap>
#include "../Plugins/CorePlugin/Interfaces/istorageadapterfactory.h"
#include "../Plugins/CorePlugin/Interfaces/IMediaCollectionBuilder.h"
#include "../Plugins/CorePlugin/Interfaces/IMediaCollection.h"
#include "CollectionController_global.h"

using namespace Core;
namespace Controller
{
    class COLLECTIONCONTROLLERSHARED_EXPORT  CollectionController:public Core::ICollectionController {

    public:
        CollectionController();
        QList<IMediaCollection*> getCollections(QString type);
        bool loadMediaCollection(QUrl filename);
        IMediaCollection* getMediaCollection(QUrl filename);

    private:

        void loadExtensionMap();
        QString getStorageTypeByFilename(QString filename);
        QMap<QString, IMediaCollection*> m_collectionMap;
        QMap<QString, IStorageAdapterFactory*> m_factoryMap;
        QMap<QString, IMediaCollectionBuilder*> m_builderMap;
        QMap<QString, QString> m_fileExtensionMap;


    signals:

        void playerWidgetChanged();
        void playlistWidgetChanged();

    private slots:

       void objectAddedToObjectPool(QObject* object);





    };
}
#endif // COLLECTIONCONTROLLER_H
