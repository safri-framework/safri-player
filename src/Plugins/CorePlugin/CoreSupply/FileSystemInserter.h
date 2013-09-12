#ifndef FILESYSTEMINSERTER_H
#define FILESYSTEMINSERTER_H

#include "../CorePlugin_global.h"

#include <QObject>

#include "Interfaces/ICore.h"
#include "../Interfaces/IMediaTagger.h"
#include "../Interfaces/IMediaCollection.h"
#include "../Interfaces/ICollectionController.h"
#include "../Interfaces/IMediaInserter.h"
#include "pluginmanager.h"

class QThread;

namespace Core
{
    class IMediaTagger;
    class IMediaCollection;

    class COREPLUGINSHARED_EXPORT FileSystemInserter : public IMediaInserter
    {
        Q_OBJECT
        public:

            explicit FileSystemInserter(IMediaCollection* collection);
            ~FileSystemInserter();
            void insertMedia(QUrl mediaUrl, IMediaTagger *tagger);

        signals:
            void finished();

        private slots:
            void start();
            void mediaTagged(MediaInfoContainer info);
            void threadFinished();

        private:
            QThread* thread;
            IMediaCollection* collection;
            QUrl mediaUrlToInsert;
            IMediaTagger* taggerForInsert;
            int numberOfFiles;
            int currentFile;

    };
}

#endif // FILESYSTEMINSERTER_H
