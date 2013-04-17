#ifndef ICOLLECTIONCONTROLLER_H
#define ICOLLECTIONCONTROLLER_H

#include <QObject>
#include <QList>
#include <QUrl>
#include "../CorePlugin_global.h"

namespace Core
{
    class IMediaCollection;

    class COREPLUGINSHARED_EXPORT ICollectionController : public QObject
    {
        Q_OBJECT

        public:

            virtual QList<IMediaCollection*>        getCollections(QString type) = 0;
            virtual bool                            loadMediaCollection(QUrl filename) = 0;
            virtual IMediaCollection*               getMediaCollection(QUrl filename) = 0;
            virtual bool                            saveCollections() = 0;

        signals:

            void mediaCollectionRemoved(QUrl filename);
            void mediaCollectionAdded(IMediaCollection* collection);
            void mediaCollectionChanged(QUrl filename);

    };
}
Q_DECLARE_INTERFACE(Core::ICollectionController, "Core::ICollectionController")



#endif // ICOLLECTIONCONTROLLER_H

