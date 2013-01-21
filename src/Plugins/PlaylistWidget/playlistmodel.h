#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractTableModel>
#include "iplaylist.h"
#include <QStringList>
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
        virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
        virtual Qt::ItemFlags flags(const QModelIndex &index) const;
        Core::IPlaylist* getPlaylist();
        virtual Qt::DropActions supportedDropActions() const;
        QStringList mimeTypes() const;


private slots:

        void positionOfActuallyPlayingSongChanged(int from, int to);
        void songsInserted(int position, int count);
        void songMoved(int from, int to);
        void songDeleted(int value);
        void songDataChanged(int position);

    private:




        QVariant dataSongDisplayRole(Core::Song* song, int column) const;

        Core::IPlaylist* playlist;

};

#endif // PLAYLISTMODEL_H
