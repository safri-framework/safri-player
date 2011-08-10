#ifndef SAFEDPLAYLISTMODEL_H
#define SAFEDPLAYLISTMODEL_H

#include <QAbstractItemModel>
#include "m3utranslator.h"
#include "playlist.h"
#include "treeitem.h"
#include <QMimeData>

class SafedPlaylistModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SafedPlaylistModel(QObject *parent = 0);


    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
 QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
QModelIndex parent(const QModelIndex& index) const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    QStringList mimeTypes() const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QMimeData* mimeData(const QModelIndexList &indexes) const;

    virtual Qt::DropActions supportedDropActions() const;



private:

TreeItem* rootItem;


signals:

public slots:

};

#endif // SAFEDPLAYLISTMODEL_H
