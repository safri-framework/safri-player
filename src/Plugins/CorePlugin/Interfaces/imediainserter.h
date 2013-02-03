#ifndef IMEDIAINSERTER_H
#define IMEDIAINSERTER_H

#include "../CorePlugin_global.h"
#include <QObject>
#include <QUrl>

namespace Core
{
    class IMediaTagger;
    class IMediaCollection;

    class COREPLUGINSHARED_EXPORT IMediaInserter : public QObject
    {
        Q_OBJECT
        public:

            explicit IMediaInserter();

            virtual void insertMedia(QUrl mediaUrl, IMediaTagger* tagger = 0) = 0;

        signals:

            void mediaInsertionStarted(IMediaCollection* collection);
            void mediaInsertionFinished(IMediaCollection* collection);
            void mediaInsertionProgress(IMediaCollection* collection, int progress, int work);
    };
}

#endif // IMEDIAINSERTER_H
