#ifndef ITEM_H
#define ITEM_H

#include "../CorePlugin_global.h"

#include <QObject>
#include <QList>

namespace Core
{
    class Media;

    class COREPLUGINSHARED_EXPORT Item : public QObject
    {
        Q_OBJECT
        public:
            Item(QObject *parent) : QObject(parent) {}
            virtual QList<Media*> getMedia() = 0;
    };
}

#endif // ITEM_H
