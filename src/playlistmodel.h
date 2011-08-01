#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QList>
#include <QUrl>
#include <QMimeData>
#include <QBrush>
#include <QColor>
#include <QIcon>
#include "playlist.h"
#include "taginserter.h"


class PlaylistModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
        explicit PlaylistModel(Playlist *sPlaylist, QObject *parent = 0);

        void setPlaylist(Playlist *sPlaylist);
        Playlist *getPlaylist();

        virtual void sort ( int column, Qt::SortOrder order = Qt::AscendingOrder );
        virtual int rowCount(const QModelIndex &parent) const;
        virtual int columnCount(const QModelIndex &parent) const;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

        virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

        virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
        QStringList mimeTypes() const;
        virtual Qt::ItemFlags flags(const QModelIndex &index) const;
        virtual QMimeData* mimeData(const QModelIndexList &indexes) const;

        virtual Qt::DropActions supportedDropActions() const;

    signals:
        void taggerStarted();
        void taggerFinished();


    public slots:

        void positionOfActuallyPlayingSongChanged(int from, int to);
        void songsInserted(int position, int count);
        void songMoved(int from, int to);
        void songDeleted(int value);
        void songDataChanged(int position);

        void taggerStartedSlot();
        void taggerFinishedSlot();

    private:

        Playlist *playlist;
        TagInserter *taggerThread;

};

#endif // PLAYLISTMODEL_H
