#include "playlistmodel.h"
#include "CoreData/media.h"
#include "CoreData/song.h"
#include "CoreData/item.h"
#include "CoreData/media.h"
#include <QDebug>
#include "Songtree/songtreeitem.h"
#include <QSize>


PlaylistModel::PlaylistModel(QSharedPointer<Core::IPlaylist> playlist, QObject *parent) :
    QAbstractTableModel(parent), playlist(playlist)
{
    connect(playlist.data(), SIGNAL(MediaInserted(int,int)), this, SLOT(songsInserted(int,int)));
    connect(playlist.data(), SIGNAL(MediaDataChanged(int)), this, SLOT(songDataChanged(int)));
    connect(playlist.data(), SIGNAL(MediaDeleted(int)), this, SLOT(songDeleted(int)));
    connect(playlist.data(), SIGNAL(MediaMoved(int,int)), this, SLOT(songMoved(int,int)));
    connect(playlist.data(), SIGNAL(changeActualPlayingMarker(int,int)), this, SLOT(positionOfActuallyPlayingSongChanged(int,int)));
}


int PlaylistModel::rowCount(const QModelIndex &parent) const
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
    return 0;}


void PlaylistModel::positionOfActuallyPlayingSongChanged(int from, int to)
{

    //qDebug()<<"from"<<from<<"  "<<"to"<<to;
    // remove the playing symbol from the old playing song
    Q_EMIT dataChanged( index(from, 0), index(from, 4) );
    // set the playing symbol to the new playing song
    Q_EMIT dataChanged( index(to, 0), index(to, 4) );
}

void PlaylistModel::songsInserted(int position, int count)
{
    qDebug()<<"INSERTED "<<count<< "songs";
    beginInsertRows( QModelIndex(), position, position + count-1);
    endInsertRows();
}

void PlaylistModel::songMoved(int from, int to)
{
    if( from  > to)
    {
        int tmp = from;
        from = to;
        to = tmp;
    }
    for(int i=from; i <= to; i++)
    {
        //qDebug() << "playlistModel media moved at row: " << i;
        Q_EMIT dataChanged( index(i, 0), index(i, 4) );
    }
}

void PlaylistModel::songDeleted(int value)
{
    beginRemoveRows(QModelIndex(), value, value);
    endRemoveRows();
    //songMoved(value, playlist->getSize()-1 );
}

void PlaylistModel::songDataChanged(int position)
{
    Q_EMIT dataChanged( index(position, 0), index(position, 6));
}


QMimeData *PlaylistModel::mimeData(const QModelIndexList &indexes) const
{
    QList<QUrl> filenames;
    QMimeData *mimeData;
    QByteArray encodedData;

    mimeData = QAbstractItemModel::mimeData(indexes);
    Core::Media* mediaAtIndex;
    foreach (QModelIndex index, indexes)
    {
        if (index.isValid())
        {
            mediaAtIndex = playlist->getMediaAt(index.row());
            int row = index.row();
            filenames.append( mediaAtIndex->getURL().toLocalFile());
            qint64 pointer = (qint64) mediaAtIndex;
            QDataStream stream(&encodedData, QIODevice::WriteOnly);
            stream <<  pointer << row;
        }
    }
    mimeData->setData("MediaFromPlaylist", encodedData);
    mimeData->setUrls(filenames);
    return mimeData;
}

void PlaylistModel::moveSong(int from, int to)
{
    playlist->moveMedia(from, to);
}


Qt::ItemFlags PlaylistModel::flags(const QModelIndex &index) const
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

int PlaylistModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return 8;
}

QHash<int, QByteArray> PlaylistModel::roleNames() const
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


QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    Core::Media* media;
    Core::Song* song;

    if ( (playlist == 0) || (!index.isValid()) )
    {
         return QVariant();
    }

    media = playlist->getMediaAt(index.row());

    if (media->getType() != Core::DataItem::SONG)
    {
        if(role == Qt::DisplayRole)
        {
                return QVariant();
        }
        else if (role == Qt::UserRole)
        {
            if (playlist->isCurrentMedia(index.row()))
                    return true;
        }
        return QVariant();
    }


    song = qobject_cast<Core::Song*>(media);
    if (!song)
    {
        return QVariant();
    }

    if (role == isPlayingRole)
    {
        return index.row() == playlist->getCurrentMediaPosition();
    }

    if (role == posRole)
    {
        return index.row();
    }

    return dataSongDisplayRole(song, role);
}

QSharedPointer<Core::IPlaylist> PlaylistModel::getPlaylist()
{
    return playlist;
}

QVariant PlaylistModel::dataSongDisplayRole(Core::Song *song, int role) const
{

    int length;
    int minutes;
    int seconds;
    int hours = 0;
    int track;
    QString lengthString;

    switch (role)
    {
        case lengthRole:

            track = song->getTrack();

            if(track < 0)
                return "";

            if (track < 10)
            {
                return "0" + QString::number(track);
            }

            return song->getTrack();

        case artistRole:

            return song->getArtist()->getName();

        case songRole:

            return song->getName();

        case albumRole:

            return song->getAlbum()->getName();

        case 5:

            return song->getGenre()->getName();

        case 7:

            length = song->getLength();

            minutes = length / 60;
            seconds = length - minutes * 60;

            if (minutes >= 60)
            {
                hours = minutes / 60;
                minutes = minutes - hours * 60;
            }


            if (hours > 0)
            {
                if (hours < 10)
                {
                    lengthString = "0";
                }
                lengthString += QString::number(hours) + ":";
            }

            if (minutes < 10)
            {
                lengthString += "0";
            }


            lengthString += QString::number(minutes) + ":";

            if (seconds < 10)
            {
                lengthString += "0";
            }

            lengthString += QString::number(seconds);

            return lengthString;

        default:

            return QVariant();
    }

    return QVariant();
}
