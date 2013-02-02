#ifndef IMEDIATAGGERFACTORY_H
#define IMEDIATAGGERFACTORY_H
#include "../CorePlugin_global.h"
#include "IMediaTagger.h"


namespace Core
{
    class COREPLUGINSHARED_EXPORT IMediaTaggerFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IMediaTaggerFactory(QObject* parent = 0);
        virtual ~IMediaTaggerFactory();

        virtual IMediaTagger* createTagger() = 0;
        virtual QString getName() = 0;




    };
}
#endif // IMEDIATAGGERFACTORY_H
