#ifndef RESTSONGTREE_H
#define RESTSONGTREE_H

#include <QObject>

namespace Core
{
    class ITreeItem;
}

namespace SafriRESTClient
{
    class RESTClient;
    class RESTSongtreeItem;

    class RESTSongtree : public QObject
    {
        Q_OBJECT
        public:

            explicit RESTSongtree(RESTClient *restClient, QObject *parent = 0);
            ~RESTSongtree();

            Core::ITreeItem* getRoot();

        private:

            RESTClient* client;
            RESTSongtreeItem* rootItem;

    };
}

#endif // RESTSONGTREE_H
