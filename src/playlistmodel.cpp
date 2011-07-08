#include "playlistmodel.h"

PlaylistModel::PlaylistModel(Playlist *sPlaylist, QObject *parent) :
    QAbstractTableModel(parent), playlist(0), taggerThread(0)
{
    setPlaylist(sPlaylist);


    Q_EMIT headerDataChanged(Qt::Horizontal, 0, 4);

}

void PlaylistModel::setPlaylist(Playlist *sPlaylist)
{

    // if changing the playlist the entire data of the view gets invalid
    beginResetModel();


        if (taggerThread != 0 && taggerThread->isRunning() )
        {
            taggerThread->stop();
            taggerThread->quit();
        }

        if (playlist != 0)
        {
            disconnect(playlist, SIGNAL(songDataChanged(int)), this, SLOT(songDataChanged(int)));
            disconnect(playlist, SIGNAL(positionOfActuallyPlayingSongChanged(int,int)), this, SLOT(positionOfActuallyPlayingSongChanged(int,int)));
            disconnect(playlist, SIGNAL(songMoved(int,int)), this, SLOT(songMoved(int,int)));
            disconnect(playlist, SIGNAL(songDeleted(int)), this, SLOT(songDeleted(int)));
        }

        playlist = sPlaylist;

        connect(playlist, SIGNAL(songDataChanged(int)), this, SLOT(songDataChanged(int)));
        connect(playlist, SIGNAL(positionOfActuallyPlayingSongChanged(int,int)), this, SLOT(positionOfActuallyPlayingSongChanged(int,int)));
        connect(playlist, SIGNAL(songMoved(int,int)), this, SLOT(songMoved(int,int)));
        connect(playlist, SIGNAL(songDeleted(int)), this, SLOT(songDeleted(int)));

        if (playlist->getSongCount() > 0)
        {
            taggerThread = new TagInserter(playlist);

            connect(taggerThread, SIGNAL(started()),this, SLOT(taggerStartedSlot()));
            connect(taggerThread, SIGNAL(finished()), this, SLOT(taggerFinishedSlot()));
            taggerThread->start();
        }

    endResetModel();



}

Playlist *PlaylistModel::getPlaylist()
{
    return playlist;
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
            return playlist->getSongCount();
        }
        else
        {
            return 0;
        }
    }
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
        }
    }

    return QVariant();
}

int PlaylistModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{

    if (playlist == 0)
    {
        return QVariant();
    }

    if ( index.isValid() )
    {

        if (role == Qt::DisplayRole)
        {

            AudioFile *audioFile = playlist->getAudioFileAt( index.row() );

            if (audioFile != 0)
            {

                switch ( index.column() )
                {
                    case 0:

                        return audioFile->getTrack();

                    case 1:

                        return audioFile->getArtist();

                    case 2:

                        return audioFile->getTitle();

                    case 3:

                        return audioFile->getAlbum();

                    case 4:

                        return audioFile->getYear();

                    case 5:

                        return audioFile->getGenre();


                    default:

                        return QVariant();
                }

            }
            else
            {
                return QVariant();
            }


        }
        else if (role == Qt::BackgroundRole)
        {
            if(playlist->isSongPlaying(index.row()))
            {
                return QBrush( QColor(90, 174, 254) );
            }
            else
            {
                return QVariant();
            }
        }
        else if (role == Qt::DecorationRole)
        {
            if(playlist->isSongPlaying(index.row()) && index.column() == 0)
            {
                return QIcon("img/play_icon.png");
            }
            else
            {
                return QVariant();
            }
        }
        else
        {
            return QVariant();
        }

    }
    else
    {
        return QVariant();
    }


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
    Q_EMIT dataChanged( index(position, 0), index(position, 4));
}

void PlaylistModel::sort( int column, Qt::SortOrder order)
{

    switch (column)
    {
        case 0:

            beginResetModel();
                playlist->sortByTrack(order);
            endResetModel();

            break;

        case 1:

            beginResetModel();
                playlist->sortByArtist(order);
            endResetModel();

            break;

        case 2:

            beginResetModel();
                playlist->sortByTitle(order);
            endResetModel();

            break;

        case 3:

            beginResetModel();
                playlist->sortByAlbum(order);
            endResetModel();

            break;

        case 4:

            beginResetModel();
                playlist->sortByYear(order);
            endResetModel();

            break;

        case 5:

            beginResetModel();
                playlist->sortByGenre(order);
            endResetModel();

            break;
    }



}


QStringList PlaylistModel::mimeTypes() const
{
    QStringList types = QAbstractItemModel::mimeTypes();
    types << "text/uri-list";

    return types;
}


Qt::ItemFlags PlaylistModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

bool PlaylistModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    bool dropped = false;


    if (action == Qt::MoveAction)
    {

        if (data->hasFormat("application/x-qabstractitemmodeldatalist"))
        {

            QByteArray encoded = data->data("application/x-qabstractitemmodeldatalist");
            QDataStream stream(&encoded, QIODevice::ReadOnly);

            int sourceRow;

            stream >> sourceRow;

            int insertLocation;

            if ( parent.isValid() )
            {
                // if something dropped on a song, use the location of the valid ModelIndex
                insertLocation = parent.row();
            }
            else
            {
                // else something dropped after the last song, so the songs have to be inserted after the last song
                insertLocation = playlist->getSongCount() - 1;
                if (insertLocation < 0)
                {
                    insertLocation = 0;
                }

            }


            this->playlist->moveSong(sourceRow, insertLocation);
            dropped = true;
        }
    }

    if (action == Qt::CopyAction)
    {
        if (data->hasFormat("text/uri-list"))
        {

            QList<QUrl> urls = data->urls();
            QList<AudioFile*> *audioFiles = new QList<AudioFile*>();

            for (int counter = 0 ; counter < urls.length(); counter ++)

            {
                AudioFile *aFile = new AudioFile(urls.at(counter).toLocalFile());

                audioFiles->append(aFile);

            }



            if (audioFiles->size() > 0)
            {

                int insertLocation;

                if ( parent.isValid() )
                {
                    // if something dropped on a song, use the location of the valid ModelIndex
                    insertLocation = parent.row();
                }
                else
                {
                    // else something dropped after the last song, so the songs have to be inserted after the last song
                    insertLocation = playlist->getSongCount() ;
                    if (insertLocation < 0)
                    {
                        insertLocation = 0;
                    }

                }

                beginInsertRows( QModelIndex(), insertLocation, insertLocation + audioFiles->size());
                    playlist->insertSongsAt(insertLocation, audioFiles);
                endInsertRows();

                if (taggerThread == 0)
                {
                    taggerThread = new TagInserter(this->playlist);
                }

                if ( !taggerThread->isRunning() )
                {
                    taggerThread = new TagInserter(this->playlist);
                    taggerThread->start();
                }

            }

            dropped = true;


        }
    }


    return dropped;
}

QMimeData *PlaylistModel::mimeData(const QModelIndexList &indexes) const
{
    QList<QUrl> filenames;
    QMimeData *mimeData;

    mimeData = QAbstractItemModel::mimeData(indexes);


    foreach (QModelIndex index, indexes) {
        if (index.isValid())
        {

            AudioFile* songAtIndex = playlist->getAudioFileAt(index.row());
            filenames.append( QUrl::fromLocalFile(songAtIndex->fileName()) );

        }

    }

    mimeData->setUrls(filenames);

    return mimeData;
}

Qt::DropActions PlaylistModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

void PlaylistModel::taggerStartedSlot()
{
    Q_EMIT taggerStarted();
}

void PlaylistModel::taggerFinishedSlot()
{
    Q_EMIT taggerFinished();
}
