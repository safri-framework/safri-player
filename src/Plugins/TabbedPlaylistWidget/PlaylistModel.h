#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractTableModel>
#include "Interfaces/IPlaylist.h"
#include <QStringList>
#include <QSharedPointer>
#include <QMimeData>
#include <QItemSelection>

namespace Core { class Song; }

class PlaylistModel : public QAbstractTableModel
{
    Q_OBJECT
    public:

        explicit PlaylistModel(QSharedPointer<Core::IPlaylist> playlist, QObject *parent = 0);
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        QVariant data(const QModelIndex &index, int role) const;
        virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
        virtual Qt::ItemFlags flags(const QModelIndex &index) const;
        QSharedPointer<Core::IPlaylist> getPlaylist();
        virtual Qt::DropActions supportedDropActions() const;
        QStringList mimeTypes() const;
        QMimeData* mimeData(const QModelIndexList &indexes) const;
        void moveSong(int from, int to);

private slots:

        void positionOfActuallyPlayingSongChanged(int from, int to);
        void songsInserted(int position, int count);
        void songMoved(int from, int to);
        void songDeleted(int value);
        void songDataChanged(int position);

    private:
        QVariant dataSongDisplayRole(Core::Song* song, int column) const;
        QSharedPointer<Core::IPlaylist> playlist;
        int getDropRow(const QModelIndex& index, int i);

    signals:
        void sizeHintChanged(QModelIndex index);
        void selectedIndexesMoved(QItemSelection &newSelection);

};

#endif // PLAYLISTMODEL_H
