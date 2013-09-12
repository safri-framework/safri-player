#ifndef MEDIA_H
#define MEDIA_H

#include "../CorePlugin_global.h"
#include <QUrl>
#include "DataItem.h"

namespace Core
{
    class COREPLUGINSHARED_EXPORT Media : public DataItem
    {
        Q_OBJECT

        public:

            Media(int sID, QString sName, DATA_ITEM_TYPE sType, QObject *parent = 0)
                : DataItem(sID, sName, sType, parent) {}

            Media(int sID, QString sName, DATA_ITEM_TYPE sType, bool temp, QObject *parent = 0)
                : DataItem(sID, sName, sType, temp, parent) {}

            virtual QUrl getURL() = 0;

            virtual QString getMimeType() = 0;
    };
}

#endif // MEDIA_H
