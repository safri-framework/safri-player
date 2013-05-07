#ifndef ABSTRACTINFORESOLVER_H
#define ABSTRACTINFORESOLVER_H

#include <QMutex>
#include "../Interfaces/IInfoResolver.h"
#include "../CorePlugin_global.h"

class QThread;

namespace Core
{
    class COREPLUGINSHARED_EXPORT AbstractInfoResolver : public IInfoResolver
    {
        Q_OBJECT

        public:

            explicit AbstractInfoResolver(QObject *parent = 0);
                                                ~AbstractInfoResolver();
            virtual QStringList                 getSupportedInfoTypes() = 0;
            virtual InfoRequest*                getInfoForItem(QString type, Core::DataItem* item);
            virtual void                        getInfo(QString type, Core::DataItem* item) = 0;
            void                                setInfo(QVariant info);

        private:

            void                                insertInFifo(InfoRequest* request);
            InfoRequest*                        getNextRequest();
            bool                                hasRequest();

            bool running;
            QList<InfoRequest*> requestList;
            QMutex  fifoMutex;
            InfoRequest* currentRequest;
            QThread* workerThread;

        private slots:

            void threadFinished();
            void workerThreadStarted();
    };
}
#endif // ABSTRACTINFORESOLVER_H
