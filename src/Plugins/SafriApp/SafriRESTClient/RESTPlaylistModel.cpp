#include "RESTPlaylistModel.h"

#include "RESTPlaylist.h"
#include "CoreData/mediainfocontainer.h"

#include <QDebug>

using namespace SafriRESTClient;

RESTPlaylistModel::RESTPlaylistModel(RESTPlaylist *playlist, QObject *parent) :
    QAbstractTableModel(parent), playlist(playlist)
{
    connect(playlist, SIGNAL(mediaMoved(int,int)), this, SLOT(mediaMoved(int,int)));
    connect(playlist, SIGNAL(beginResetModel()), this, SLOT(beginModelReset()));
    connect(playlist, SIGNAL(endResetModel()),this, SLOT(endModelReset()));
    connect(playlist, SIGNAL(currentMediaPositionChanged(int,int)), this, SLOT(positionOfCurrentPlayingSongChanged(int,int)));
    connect(playlist, SIGNAL(mediaDeleted(int)), this, SLOT(mediaDeleted(int)));
}

// **** BEGIN QAbstractTableModel Interface Implementation ****

int RESTPlaylistModel::rowCount(const QModelIndex &parent) const
{
    if ( parent.isValid() )
    {
        return 0;
    }
    else
    {
        if (playlist != 0)
        {
            return playlist->getSize();
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

int RESTPlaylistModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

Qt::ItemFlags RESTPlaylistModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
    {
        if(playlist->getSize() > 0)
        {
            return defaultFlags;
        }
        else
        {
            return Qt::ItemIsDropEnabled;
        }
    }
}

void RESTPlaylistModel::beginModelReset()
{
    beginResetModel();
}

void RESTPlaylistModel::endModelReset()
{
    endResetModel();
}

QVariant RESTPlaylistModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    Core::MediaInfoContainer* infoContainer = playlist->getMediaInfoAt(index.row());

    switch (role)
    {
        case Qt::DisplayRole:

            return infoContainer->getMediaInfo(Core::InfoTitle);

        case songRole:

            return infoContainer->getMediaInfo(Core::InfoTitle);

        case artistRole:

            return infoContainer->getMediaInfo(Core::InfoArtist);

        case albumRole:

            return infoContainer->getMediaInfo(Core::InfoAlbum);

        case posRole:

            return index.row();
        case isPlayingRole:
            return index.row() == playlist->getCurrentMediaPosition();

        default:

            return QVariant();
    }
}

QHash<int, QByteArray> RESTPlaylistModel::roleNames() const
{

    QHash<int, QByteArray> roles;
    roles[songRole] = "song";
    roles[artistRole] = "artist";
    roles[albumRole] = "album";
    roles[posRole] = "position";
    roles[Qt::DisplayRole] ="display";
    roles[isPlayingRole] ="isPlaying";

    return roles;
}



// **** END QAbstractTableModel Interface Implementation ****

void RESTPlaylistModel::positionOfCurrentPlayingSongChanged(int oldIndex, int newIndex)
{
    Q_EMIT dataChanged(index(oldIndex,0),index(oldIndex,0));
    Q_EMIT dataChanged(index(newIndex,0),index(newIndex,0));
}

void RESTPlaylistModel::mediaDeleted(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    endRemoveRows();
}

void RESTPlaylistModel::mediaMoved(int fromPosition, int toPosition)
{
    /*
    if( fromPosition  > toPosition)
    {
        int tmp = fromPosition;
        fromPosition = toPosition;
        toPosition = tmp;
    }
    for(int i = fromPosition; i <= toPosition; i++)
    {
        qDebug() << "playlistModel media moved at row: " << i;

        Q_EMIT dataChanged( index(i, 0), index(i, 4) );
    }
    */

    int offset = 0;

    // BUG:
    /* In this case the QML ListView doesn't react on the dataChanged signal, although it
     * works in the NON-REST PlaylistModel. Seems to be a bug in Qt/QML.
     */

    if (fromPosition < toPosition)
    {
        offset = 1;
    }

    beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition + offset);
    endMoveRows();

}
