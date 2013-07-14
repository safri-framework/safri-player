#ifndef RESTAPPCONTROLLER_H
#define RESTAPPCONTROLLER_H

#include "IAppController.h"

namespace SafriRESTClient
{
    class RESTAppController : public IAppController
    {
        Q_OBJECT
        public:

            explicit RESTAppController(QObject *parent = 0);

            virtual QAbstractItemModel* getSongtreeModel();
    };
}

#endif // RESTAPPCONTROLLER_H
