#ifndef DTOCHANGER_H
#define DTOCHANGER_H

#include <QObject>
#include <QModelIndex>

class BaseDTO;


class DTOChanger : public QObject
{
    Q_OBJECT
    public:
        explicit DTOChanger(BaseDTO *dto, QModelIndex &index, QObject *parent = 0);

    signals:

        void AlbumCoverChanged();
        void ModelIndexDataChanged(QModelIndex);

    public slots:

        void changeAlbumCover();

    private:

        BaseDTO* dto;
        QModelIndex &index;

};

#endif // DTOCHANGER_H
