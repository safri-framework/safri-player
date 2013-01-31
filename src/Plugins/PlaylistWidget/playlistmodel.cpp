#include "playlistmodel.h"
#include "CoreData/media.h"
#include "CoreData/song.h"
#include "CoreData/item.h"
#include "CoreData/media.h"
#include <QDebug>
#include "Songtree/songtreeitem.h"
#include <QMimeData>


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

    return 0;
}

bool PlaylistModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    QList<Core::Media*> mediaList;

    if (data->hasFormat("Item"))
    {

        QByteArray encodedData = data->data("Item");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        QList<Core::Item*> draggedItems;


        while (!stream.atEnd()) {
            qint64 id;
            int row;
            int column;
            QString text;
            qint64 pointer = 0;
            stream >> id >> row >> column >> text >> pointer ;
            //newItems[id][row][column] = text;
            Core::SongTreeItem* treeItem =(Core::SongTreeItem*) pointer;
            draggedItems.append(static_cast<Core::Item*>(treeItem));
            //draggedItems.append(item);
            qDebug()<<pointer;


        }

        qDebug()<<draggedItems.size();
        qDebug() << draggedItems.at(0)->getMedia().size();
/*
        for ( int i = 0; i < draggedItems.size(); i++)
        {

        }
*/
        int row = parent.row();
        if(row < 0)
           row = 0;

        for(int i=0; i<draggedItems.size(); i++)
        {

            playlist->insertMediaAt(row, draggedItems);
        }



    }
}

Qt::DropActions PlaylistModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}


QStringList PlaylistModel::mimeTypes() const
{
    QStringList types = QAbstractItemModel::mimeTypes();
    types << "text/uri-list";

    return types;
}



void PlaylistModel::positionOfActuallyPlayingSongChanged(int from, int to)
{
    // remove the playing symbol from the old playing song
    Q_EMIT dataChanged( index(from, 0), index(from, 4) );

    // set the playing symbol to the new playing song
    Q_EMIT dataChanged( index(to, 0), index(to, 4) );
}

void PlaylistModel::songsInserted(int position, int count)
{
    qDebug()<<"INSERTED "<<count<< "songs";
    beginInsertRows( QModelIndex(), position, position + count);
    endInsertRows();
}

void PlaylistModel::songMoved(int from, int to)
{
    //beginMoveRows(QModelIndex(), from, from, QModelIndex(), to);
    //endMoveRows();
    // This version was not working by moving a song from one line to the next.



    Q_EMIT dataChanged( index(from, 0), index(from, 4) );
    Q_EMIT dataChanged( index(to, 0), index(to, 4) );

}

void PlaylistModel::songDeleted(int value)
{
    beginRemoveRows(QModelIndex(), value, value);
    endRemoveRows();
}

void PlaylistModel::songDataChanged(int position)
{
    Q_EMIT dataChanged( index(position, 0), index(position, 6));
}





Qt::ItemFlags PlaylistModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

int PlaylistModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return 7;
}

QVariant PlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole )
    {

        switch (section)
        {

            case 0:
                return "Track";

            case 1:
                return "Interpret";

            case 2:
                return "Titel";

            case 3:
                return "Album";

            case 4:
                return "Jahr";

            case 5:
                return "Genre";

            case 6:
                return "Länge";
        }
    }

    return QVariant();
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
        return QVariant();
    }

    song = qobject_cast<Core::Song*>(media);
    if (!song)
    {
        return QVariant();
    }

    switch (role)
    {
        case Qt::DisplayRole:

            return dataSongDisplayRole(song, index.column());
            break;

        case Qt::DecorationRole:

            //if (playlist->isCurrentMedia())

            break;

        default:

            break;
    }

    return QVariant();
}

QSharedPointer<Core::IPlaylist> PlaylistModel::getPlaylist()
{
    return playlist;
}

QVariant PlaylistModel::dataSongDisplayRole(Core::Song *song, int column) const
{
    int length;
    int minutes;
    int seconds;
    int hours = 0;
    int track;
    QString lengthString;

    switch (column)
    {
        case 0:

            track = song->getTrack();

            if (track < 10)
            {
                return "0" + QString::number(track);
            }

            return song->getTrack();

        case 1:

            return song->getArtist()->getName();

        case 2:

            return song->getName();

        case 3:

            return song->getAlbum()->getName();

        case 4:

            return song->getYear();

        case 5:

            return song->getGenre()->getName();

        case 6:

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
