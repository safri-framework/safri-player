#ifndef RESTAPPCONTROLLER_H
#define RESTAPPCONTROLLER_H

#include "IAppController.h"

namespace SafriRESTClient
{
    class RESTSongtreeModel;
    class RESTSongtree;
    class RESTPlaylist;
    class RESTPlaylistModel;
    class RESTClient;

    class RESTAppController : public IAppController
    {
        Q_OBJECT
        public:

            explicit RESTAppController(QObject *parent = 0);

            virtual QAbstractItemModel*         getSongtreeModel();
            virtual QAbstractItemModel*         getPlaylistModel();
            virtual void                        moveMediaInPlaylist(int from, int to);
            virtual void                        playTreeModelIndex(QModelIndex treeIndex);

        private:

            QString                             getRESTLocation();
            void                                insertSongtreeNodeInPlaylist(int itemID, int position = -1);

            RESTClient*             restClient;
            RESTSongtree*           songtree;
            RESTSongtreeModel*      songtreeModel;
            RESTPlaylist*           playlist;
            RESTPlaylistModel*      playlistModel;
    };
}

#endif // RESTAPPCONTROLLER_H
