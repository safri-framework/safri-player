#ifndef IAPPCONTROLLER_H
#define IAPPCONTROLLER_H

#include <QObject>
#include <QModelIndex>

class QAbstractItemModel;

class IAppController : public QObject
{
    Q_OBJECT
    public:

        explicit IAppController(QObject *parent = 0);
        virtual ~IAppController();

        enum APP_MODE { LOCAL, REST };

        virtual QAbstractItemModel*         getSongtreeModel() = 0;
        virtual QAbstractItemModel*         getPlaylistModel() = 0;
        virtual void                        moveMediaInPlaylist(int from, int to) = 0;
        virtual void                        playTreeModelIndex(QModelIndex treeIndex) = 0;
        virtual void                        enqueueTreeModelIndex(QModelIndex treeIndex) = 0;
        virtual void                        playPlaylistIndex(int index) = 0;
        virtual void                        removeIndexFromPlaylist(int index) = 0;
        virtual void                        setShuffle(bool enabled) = 0;
        virtual APP_MODE                    getMode() = 0;
        virtual void                        shutdown() = 0;

    signals:

        void newPlaylistModel();
};

#endif // IAPPCONTROLLER_H
