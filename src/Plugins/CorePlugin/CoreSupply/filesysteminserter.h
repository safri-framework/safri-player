#ifndef FILESYSTEMINSERTER_H
#define FILESYSTEMINSERTER_H

#include "../CorePlugin_global.h"
#include "../Interfaces/imediainserter.h"

namespace Core
{
    class COREPLUGINSHARED_EXPORT FileSystemInserter : public IMediaInserter
    {
        Q_OBJECT
        public:

            explicit FileSystemInserter(IMediaCollection* collection);

            void insertMedia(QUrl mediaUrl, IMediaTagger *tagger);



        public slots:

            Q_INVOKABLE void errorMessage(QString error);
            Q_INVOKABLE void mediaInsertionFinished();

        private:

            IMediaCollection* collection;
            IMediaTagger* tagger;

    };
}
#endif // FILESYSTEMINSERTER_H
