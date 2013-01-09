#ifndef ICOLLECTIONCONTROLLER_H
#define ICOLLECTIONCONTROLLER_H
#include <QList>
#include <QUrl>
#include "IMediaCollection.h"
#include "CorePlugin_global.h"

namespace Core
{
    class COREPLUGINSHARED_EXPORT ICollectionController : public QObject
    {
        Q_OBJECT

        public:
            virtual QList<IMediaCollection*> getCollections(QString type) = 0;
            virtual bool loadMediaCollection(QUrl filename) = 0;
            virtual IMediaCollection* getMediaCollection(QUrl filename) = 0;

        signals:

            void playerWidgetChanged();
            void playlistWidgetChanged();



    };
}
Q_DECLARE_INTERFACE(Core::ICollectionController, "Core::ICollectionController")



#endif // ICOLLECTIONCONTROLLER_H

