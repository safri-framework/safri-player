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
    
        virtual QAbstractItemModel*         getSongtreeModel() = 0;
        virtual QAbstractItemModel*         getPlaylistModel() = 0;
        virtual void                        moveMediaInPlaylist(int from, int to) = 0;
        virtual void                        playTreeModelIndex(QModelIndex treeIndex) = 0;
};

#endif // IAPPCONTROLLER_H
