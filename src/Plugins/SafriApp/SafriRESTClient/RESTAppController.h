#ifndef RESTAPPCONTROLLER_H
#define RESTAPPCONTROLLER_H

#include "IAppController.h"
#include <QTimer>

namespace Core
{
    class IPlaybackController;
}

namespace SafriRESTClient
{
    class RESTSongtreeModel;
    class RESTSongtree;
    class RESTPlaylist;
    class RESTPlaylistModel;
    class RESTPlaybackController;
    class RESTClient;

    class RESTAppController : public IAppController
    {
        Q_OBJECT
        public:

            explicit RESTAppController(QObject *parent = 0);
            virtual ~RESTAppController();

            virtual QAbstractItemModel*         getSongtreeModel();
            virtual QAbstractItemModel*         getPlaylistModel();
            virtual void                        moveMediaInPlaylist(int from, int to);
            virtual void                        playTreeModelIndex(QModelIndex treeIndex);
            virtual void                        enqueueTreeModelIndex(QModelIndex treeIndex);
            virtual void                        playPlaylistIndex(int index);
            virtual void                        removeIndexFromPlaylist(int index);
            virtual void                        setShuffle(bool enabled);


        private:

            QString                             getRESTLocation();
            void                                insertSongtreeNodeInPlaylist(int itemID, int position = -1);


            RESTClient*                 restClient;
            RESTSongtree*               songtree;
            RESTSongtreeModel*          songtreeModel;
            RESTPlaylist*               playlist;
            RESTPlaylistModel*          playlistModel;
            RESTPlaybackController*     restPlaybackController;
            QTimer*                     versionCheckTimer;


            /**
             * @brief holds the pointer to the original (local) playback controller, so that we
             *        are able to switch back to this, if we disconnect from the REST server
             */
            Core::IPlaybackController*  localPlaybackController;

        private slots:
            void                    resetPlaylistModel();
          //  void                    versionTimeoutSlot();
          //  void                    comparePlaylistVersion();
    };
}

#endif // RESTAPPCONTROLLER_H
