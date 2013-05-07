#ifndef COLLECTIONCONTROLLER_H
#define COLLECTIONCONTROLLER_H

#include "../Plugins/CorePlugin/Interfaces/ICollectionController.h"
#include <QMap>
#include "CollectionController_global.h"

using namespace Core;

namespace Core
{
    class IMediaCollection;
    class IMediaCollectionStorageFactory;
}

namespace Controller
{
    class COLLECTIONCONTROLLERSHARED_EXPORT  CollectionController : public Core::ICollectionController
    {

    public:

        CollectionController();
        QList<IMediaCollection*>                        getCollections(QString type);
        bool                                            loadMediaCollection(QUrl filename);
        IMediaCollection*                               getMediaCollection(QUrl filename);
        virtual IMediaCollection*                       getMediaCollectionByHash(QString hash);
        virtual bool                                    saveCollections();

    private slots:

       void                                             objectAddedToObjectPool(QObject* object);

    private:

        void                                            loadExtensionMap();
        QString                                         getStorageTypeByFilename(QUrl filename);

        QMap<QString, IMediaCollection*>                m_collectionMap;
        QMap<QString, IMediaCollection*>                m_collectionHashMap;
        QMap<QString, IMediaCollectionStorageFactory*>  m_storageFactories;
        QMap<QString, QString>                          m_fileExtensionMap;

    };
}
#endif // COLLECTIONCONTROLLER_H
