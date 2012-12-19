#include "playlistmodel.h"
#include "CoreData/media.h"
#include "CoreData/song.h"
#include <QDebug>

PlaylistModel::PlaylistModel(Core::IPlaylist *playlist, QObject *parent) :
    QAbstractTableModel(parent), playlist(playlist)
{
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
    }

    return QVariant();
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
