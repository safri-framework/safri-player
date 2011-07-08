#include "dtochanger.h"

#include "basedto.h"
#include "databasedao.h"

#include <QDebug>
#include <QFileDialog>

DTOChanger::DTOChanger(BaseDTO *dto, QModelIndex &index, QObject *parent) :
    QObject(parent), dto(dto), index(index)
{

}


void DTOChanger::changeAlbumCover()
{
    if (dto->getType() == BaseDTO::ALBUM )
    {
        QString filename = QFileDialog::getOpenFileName(0, "Wähle Cover für " + dto->getText(), "", "Images (*.png *.xpm *.jpg)");

        if ( !filename.isEmpty() )
        {
            DatabaseDAO::changeAlbumCover(filename, dto->getID());
            Q_EMIT AlbumCoverChanged();

            if (index.isValid())
            {
                Q_EMIT ModelIndexDataChanged(index);
            }
           }
    }
}
