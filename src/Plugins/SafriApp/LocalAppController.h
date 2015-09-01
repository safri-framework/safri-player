#ifndef LOCALAPPCONTROLLER_H
#define LOCALAPPCONTROLLER_H

#include "IAppController.h"

#include <QSharedPointer>

namespace Core
{
    class SongTree;
    class ITreeItemType;
    class IPlaylist;
    class Song;
}

class PlaylistModel;

class LocalAppController : public IAppController
{
    Q_OBJECT
    public:

        explicit LocalAppController(QObject *parent = 0);

        virtual QAbstractItemModel*         getSongtreeModel(TREE_HIERARCHY);
        virtual QAbstractItemModel*         getPlaylistModel();
        virtual QAbstractItemModel*         getCoverModel();
        virtual void                        moveMediaInPlaylist(int from, int to);
        virtual void                        playTreeModelIndex(QModelIndex treeIndex);
        virtual void                        enqueueTreeModelIndex(QModelIndex treeIndex);
        virtual void                        playPlaylistIndex(int index);
        virtual void                        removeIndexFromPlaylist(int index);
        virtual void                        setShuffle(bool enabled);
        virtual APP_MODE                    getMode();
        virtual void                        shutdown();

    private:

        QList<Core::ITreeItemType*>*                createTreeHierachy(TREE_HIERARCHY hierarchy);
        QSharedPointer<Core::IPlaylist>             playlist;
        PlaylistModel*                              playlistModel;
        QList<Core::ITreeItemType *> *              treeHierarchy;
        SongTreeModel*                              model;
        SongTreeModel*                              coverModel;
        Core::SongTree*                             songTree;
        Core::SongTree*                             coverSongTree;







    private slots:
        void pbControllerHasNewPlaylist();
};

#endif // LOCALAPPCONTROLLER_H
