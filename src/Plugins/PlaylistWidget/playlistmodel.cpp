#include "playlistmodel.h"
#include "CoreData/Media.h"
#include "CoreData/Song.h"
#include "CoreData/Item.h"
#include "CoreData/Media.h"
#include <QDebug>
#include "Songtree/SongTreeItem.h"
#include <QSize>
#include <QDataStream>

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

bool PlaylistModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{

    Q_UNUSED(action)
    Q_UNUSED(row)
    Q_UNUSED(column)
    QList<Core::Media*> mediaList;

    qDebug()<<"DROP";
    if (data->hasFormat("Item"))
    {
        QByteArray encodedData = data->data("Item");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);
        QList<Core::Item*> draggedItems;

        while (!stream.atEnd()) {

            qint64 pointer = 0;
            stream  >> pointer ;
            Core::SongTreeItem* treeItem =(Core::SongTreeItem*) pointer;
            draggedItems.append(static_cast<Core::Item*>(treeItem));
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

        if(parent.isValid())
        {
            for(int i=0; i<draggedItems.size(); i++)
            {
                playlist->insertMediaAt(row, draggedItems);
            }
        }
        else
        {
            for(int i=0; i<draggedItems.size(); i++)
            {
                playlist->insertMediaAt(playlist->getSize(), draggedItems);
            }
        }
    }

    if(data->hasFormat("MediaFromPlaylist"))
    {
        QByteArray encodedData = data->data("MediaFromPlaylist");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);
        QList<Core::Media*> draggedItems;
        QList<int> draggedRows;
        int draggedFromRow = 0;
        while (!stream.atEnd())
        {
            qint64 pointer = 0;
            stream  >> pointer >> draggedFromRow ;
            Core::Media* mediaItem =(Core::Media*) pointer;
            draggedItems.append(mediaItem);
            draggedRows.append(draggedFromRow);
            qDebug()<< pointer << draggedFromRow;
        }

        for(int i = 0; i < draggedRows.size(); i++)
        {
             playlist->moveMedia(draggedRows.at(i), parent.row()+i);
        }
    }
    return true;
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
    Q_EMIT sizeHintChanged(index(to, 0));
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
    //mimeData->setUrls(filenames);
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

QVariant PlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if ( orientation == Qt::Horizontal)
    {
        if( role == Qt::DisplayRole )
        {

            switch (section)
            {

                case 1:
                    return "#";

                case 2:
                    return "Interpret";

                case 3:
                    return "Titel";

                case 4:
                    return "Album";

                case 6:
                    return "Jahr";

                case 5:
                    return "Genre";

                case 7:
                    return "Länge";
            }
        }

        if (role == Qt::SizeHintRole)
        {
            switch(section)
            {
            case 0:
                return QSize(20,20);
            case 1:
                return QSize(20,20);
            default:
                return QVariant();
            }
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
        if(role == Qt::DisplayRole)
        {
            if(index.column() == 3)
                return media->getName();
            else
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

    switch (role)
    {
        case Qt::DisplayRole:

            return dataSongDisplayRole(song, index.column());
            break;

        case Qt::UserRole:

            if (playlist->isCurrentMedia(index.row()))
                    return true;

        case Qt::UserRole+1:

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
        case 1:

            track = song->getTrack();

            if(track < 0)
                return "";

            if (track < 10)
            {
                return "0" + QString::number(track);
            }

            return song->getTrack();

        case 2:

            return song->getArtist()->getName();

        case 3:

            return song->getName();

        case 4:

            return song->getAlbum()->getName();

        case 6:

            return song->getYear();

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
