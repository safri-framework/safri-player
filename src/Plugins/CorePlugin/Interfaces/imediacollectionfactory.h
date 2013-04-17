#ifndef IMEDIACOLLECTIONFACTORY_H
#define IMEDIACOLLECTIONFACTORY_H

#include <QObject>
#include <QString>
#include "CorePlugin_global.h"

namespace Core
{
    class IMediaCollection;

    class COREPLUGINSHARED_EXPORT IMediaCollectionFactory : public QObject
    {
        Q_OBJECT
        public:
            explicit IMediaCollectionFactory(QObject *parent = 0);

            virtual QString             getCollectionType() = 0;
            virtual IMediaCollection*   createMediaCollection(QString name) = 0;
    };
}

#endif // IMEDIACOLLECTIONFACTORY_H
