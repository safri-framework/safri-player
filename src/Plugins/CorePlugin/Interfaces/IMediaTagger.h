#ifndef IMEDIATAGGER_H
#define IMEDIATAGGER_H
#include "../CorePlugin_global.h"
#include <QObject>
#include <QUrl>
#include "../CoreData/mediainfocontainer.h"


namespace Core
{
    class COREPLUGINSHARED_EXPORT IMediaTagger : public QObject
    {

        Q_OBJECT
        public:

            explicit IMediaTagger(QObject* parent);
            virtual ~IMediaTagger();

        public slots:

            virtual void tagMedia(QUrl media) = 0;

        signals:

            void mediaTagged(MediaInfoContainer &info);
            void unknownMedia(QUrl media);
    };
}

Q_DECLARE_INTERFACE(Core::IMediaTagger, "Core::IMediaTagger")

#endif // IMEDIATAGGER_H
