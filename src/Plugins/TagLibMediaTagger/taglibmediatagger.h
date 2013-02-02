#ifndef TAGLIBMEDIATAGGER_H
#define TAGLIBMEDIATAGGER_H
#include "../CorePlugin/Interfaces/IMediaTagger.h"

using namespace Core;

class TaglibMediaTagger : public IMediaTagger
{
Q_OBJECT
public:

    TaglibMediaTagger(QObject* parent);

public slots:
     void tagMedia(QUrl media);
};

#endif // TAGLIBMEDIATAGGER_H
