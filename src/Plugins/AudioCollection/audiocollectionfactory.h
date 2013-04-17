#ifndef AUDIOCOLLECTIONFACTORY_H
#define AUDIOCOLLECTIONFACTORY_H

#include "Interfaces/imediacollectionfactory.h"

class AudioCollectionFactory : public Core::IMediaCollectionFactory
{
    Q_OBJECT
    public:
        explicit AudioCollectionFactory(QObject *parent = 0);

        virtual QString                     getCollectionType();
        virtual Core::IMediaCollection*     createMediaCollection(QString name);
};

#endif // AUDIOCOLLECTIONFACTORY_H
