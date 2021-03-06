#ifndef IMEDIACOLLECTION_H
#define IMEDIACOLLECTION_H

#include "../CorePlugin_global.h"
#include "../CoreData/DataItem.h"
#include "../CoreData/Media.h"
#include "../CoreData/MediaInfoContainer.h"
#include <QUrl>
#include "../CoreData/MediaInfoContainer.h"

class InfoContainer;
namespace Core
{
    class IMediaTagger;
    class COREPLUGINSHARED_EXPORT IMediaCollection : public QObject
    {
        Q_OBJECT
        public:

            explicit IMediaCollection(QObject* parent);
            virtual ~IMediaCollection();

            virtual QList<Core::DataItem*> getByName(DataItem::DATA_ITEM_TYPE type, QString name) = 0;
            virtual Core::DataItem* getByID(DataItem::DATA_ITEM_TYPE type, int id) = 0;
            virtual QList<Core::DataItem*> getDataItems(DataItem::DATA_ITEM_TYPE type) = 0;
            virtual QList<Core::Media*> getMedia() = 0;
            virtual Core::Media* getMediaByURL(const QUrl &url) = 0;
            virtual QString getName() = 0;
            virtual QUrl getAssetFolderPath(QString subfolder) = 0;
            virtual bool isAvailable() = 0;
            virtual QUrl getRootPath() = 0;
            virtual QString getHash() = 0;
            virtual QUrl getDatabaseLocation() = 0;
            virtual void setDatabaseLocation(QUrl url) = 0;
            virtual InfoContainer* getInfoContainerByName(QString name) = 0;
            virtual QString getContentType() = 0;
            virtual void lockForWrite() = 0;
            virtual void lockForRead() = 0;
            virtual void unlock() = 0;
            virtual Media* addMedia(MediaInfoContainer &container) = 0;

        signals:
            void itemAdded(Core::DataItem* item);
            void itemRemoved(Core::DataItem* item);    

    };
}

Q_DECLARE_INTERFACE(Core::IMediaCollection, "Core::IMediaCollection")

#endif // IMEDIACOLLECTION_H
