#ifndef RESTSONG_H
#define RESTSONG_H

#include <QJsonObject>
#include "CoreData/Song.h"

namespace SafriRESTClient
{
    class RESTSong : public Core::Song
    {
        Q_OBJECT
        public:

            explicit RESTSong(QJsonObject jsonObject, QObject *parent = 0);

        signals:

        public slots:

    };
}

#endif // RESTSONG_H
