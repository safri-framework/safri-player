#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractTableModel>
#include "iplaylist.h"
#include <QStringList>
#include <QSharedPointer>
#include <QMimeData>

namespace Core { class Song; }

class PlaylistModel : public QAbstractTableModel
{
    Q_OBJECT
    public:
        explicit PlaylistModel(QSharedPointer<Core::IPlaylist> playlist, QObject *parent = 0);
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        virtual Qt::ItemFlags flags(const QModelIndex &index) const;
        QSharedPointer<Core::IPlaylist> getPlaylist();
        QMimeData* mimeData(const QModelIndexList &indexes) const;
        void moveSong(int from, int to);
        virtual QHash<int, QByteArray> roleNames() const;

private slots:
        void positionOfActuallyPlayingSongChanged(int from, int to);
        void songsInserted(int position, int count);
        void songMoved(int from, int to);
        void songDeleted(int value);
        void songDataChanged(int position);

    private:
        enum PlaylistRoles
        {
            songRole = Qt::UserRole + 1,
            artistRole = Qt::UserRole + 2,
            albumRole = Qt::UserRole + 3,
            lengthRole = Qt::UserRole + 4,
            isPlayingRole = Qt::UserRole + 5,
            posRole = Qt::UserRole + 6
        };
        QVariant dataSongDisplayRole(Core::Song* song, int role) const;
        QSharedPointer<Core::IPlaylist> playlist;
};

#endif // PLAYLISTMODEL_H
