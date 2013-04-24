#ifndef INFOCONTROLLER_H
#define INFOCONTROLLER_H

#include <CorePlugin_global.h>
#include <QObject>
#include <QMap>

class InfoRequest;
class IInfoResolver;
class DataItem;

namespace Core
{
    class IInfoResolver;
    class InfoRequest;
    class DataItem;
}

namespace Controller
{
    class COREPLUGINSHARED_EXPORT InfoController : public QObject
    {
        Q_OBJECT
        public:

            explicit                InfoController(QObject *parent = 0);

            InfoRequest*            getInfoForItem(QString type, DataItem* item);

        private slots:

            void                    objectAddedToObjectPool(QObject *object);

        private:

            QMap<QString, IInfoResolver*> resolver;

    };
}

#endif // INFOCONTROLLER_H
