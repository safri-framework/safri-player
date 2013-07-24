#ifndef RESTPLAYLISTMODEL_H
#define RESTPLAYLISTMODEL_H

#include <QAbstractTableModel>

namespace SafriRESTClient
{
    class RESTPlaylist;

    class RESTPlaylistModel : public QAbstractTableModel
    {
        Q_OBJECT
        public:

            explicit RESTPlaylistModel(RESTPlaylist *playlist, QObject *parent = 0);

            // **** BEGIN QAbstractTableModel Interface ****
            int rowCount(const QModelIndex & parent = QModelIndex()) const;
            int columnCount(const QModelIndex & parent = QModelIndex()) const;
            QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
            QHash<int, QByteArray> roleNames() const;
            Qt::ItemFlags flags(const QModelIndex &index) const;
            // **** END QAbstractTableModel Interface ****

        private slots:
            void beginModelReset();
            void endModelReset();
            void mediaMoved(int fromPosition, int toPosition);
            void positionOfCurrentPlayingSongChanged(int oldIndex, int newIndex);

        private:

            RESTPlaylist* playlist;

            enum PlaylistRoles
            {
                songRole = Qt::UserRole + 1,
                artistRole = Qt::UserRole + 2,
                albumRole = Qt::UserRole + 3,
                lengthRole = Qt::UserRole + 4,
                isPlayingRole = Qt::UserRole + 5,
                posRole = Qt::UserRole + 6
            };
    };
}

#endif // RESTPLAYLISTMODEL_H
