#ifndef RESTAPPCONTROLLER_H
#define RESTAPPCONTROLLER_H

#include "IAppController.h"

namespace SafriRESTClient
{
    class RESTSongtreeModel;
    class RESTSongtree;

    class RESTAppController : public IAppController
    {
        Q_OBJECT
        public:

            explicit RESTAppController(QObject *parent = 0);

            virtual QAbstractItemModel* getSongtreeModel();

        private:

            QString getRESTLocation();

            RESTSongtree* songtree;
            RESTSongtreeModel* songtreeModel;
    };
}

#endif // RESTAPPCONTROLLER_H
