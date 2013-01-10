#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractTableModel>
#include "iplaylist.h"

namespace Core { class Song; }

class PlaylistModel : public QAbstractTableModel
{
    Q_OBJECT
    public:

        explicit PlaylistModel(Core::IPlaylist* playlist, QObject *parent = 0);

        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;

        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        QVariant data(const QModelIndex &index, int role) const;

        Core::IPlaylist* getPlaylist();

    private:

        QVariant dataSongDisplayRole(Core::Song* song, int column) const;

        Core::IPlaylist* playlist;

};

#endif // PLAYLISTMODEL_H
