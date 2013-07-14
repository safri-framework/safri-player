#ifndef RESTMEDIACOLLECTION_H
#define RESTMEDIACOLLECTION_H

#include "Interfaces/IMediaCollection.h"

namespace SafriRESTClient
{
    class RESTMediaCollection : public Core::IMediaCollection
    {
        Q_OBJECT
        public:
            explicit RESTMediaCollection(QObject *parent = 0);

        signals:

        public slots:

    };
}

#endif // RESTMEDIACOLLECTION_H
