#ifndef FILESYSTEMINSERTERWORKER_H
#define FILESYSTEMINSERTERWORKER_H

#include <QObject>
#include "../CorePlugin_global.h"
#include "../CoreData/mediainfocontainer.h"

#include <QUrl>

namespace Core
{
    class IMediaTagger;
    class IMediaCollection;

    class COREPLUGINSHARED_EXPORT FileSystemInserterWorker : public QObject
    {
        Q_OBJECT
        public:
            explicit FileSystemInserterWorker(IMediaCollection* collection, QUrl mediaUrl, IMediaTagger *tagger);
            ~FileSystemInserterWorker();

        public slots:

            void process();
            void mediaTagged(MediaInfoContainer info);

        signals:

            Q_INVOKABLE void finished();
            Q_INVOKABLE void mediaInsertionFinished();
            Q_INVOKABLE void error(QString err);

        private:

            IMediaCollection* collection;
            QUrl mediaUrlToInsert;
            IMediaTagger* taggerForInsert;
            int numberOfFiles;
            int currentFile;

    };
}
#endif // FILESYSTEMINSERTERWORKER_H
