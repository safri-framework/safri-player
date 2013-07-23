#ifndef LOCALAPPCONTROLLER_H
#define LOCALAPPCONTROLLER_H

#include "IAppController.h"

#include <QSharedPointer>

namespace Core
{
    class SongTree;
    class ITreeItemType;
    class IPlaylist;
}

class PlaylistModel;

class LocalAppController : public IAppController
{
    Q_OBJECT
    public:

        explicit LocalAppController(QObject *parent = 0);

        virtual QAbstractItemModel*         getSongtreeModel();
        virtual QAbstractItemModel*         getPlaylistModel();
        virtual void                        moveMediaInPlaylist(int from, int to);
        virtual void                        playTreeModelIndex(QModelIndex treeIndex);

    private:

        QList<Core::ITreeItemType*>*        createTreeHierachy();

        Core::SongTree*                             songTree;
        QSharedPointer<Core::IPlaylist>             playlist;
        PlaylistModel*                              playlistModel;
};

#endif // LOCALAPPCONTROLLER_H