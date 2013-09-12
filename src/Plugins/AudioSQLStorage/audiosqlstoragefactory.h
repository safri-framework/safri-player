#ifndef AUDIOSQLSTORAGEFACTORY_H
#define AUDIOSQLSTORAGEFACTORY_H

#include "AudioSQLStorage_global.h"
#include "Interfaces/IMediaCollectionStorageFactory.h"

class AUDIOSQLSTORAGESHARED_EXPORT AudioSQLStorageFactory : public Core::IMediaCollectionStorageFactory
{
    Q_OBJECT
    public:

        explicit AudioSQLStorageFactory(QObject *parent = 0);

        virtual QString                         getStorageType();
        virtual Core::IMediaCollectionStorage*  createMediaCollectionStorage(QUrl url);
};

#endif // AUDIOSQLSTORAGEFACTORY_H
