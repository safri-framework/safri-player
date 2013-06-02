#include "AlbumCoversAssetService.h"
#include "Interfaces/IMediaCollection.h"
#include "CoreData/album.h"
#include "Interfaces/ICollectionController.h"
#include "CoreSupply/infocontroller.h"
#include "CoreSupply/InfoRequest.h"
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QImage>
#include "icore.h"

AlbumCoversAssetService::AlbumCoversAssetService(QObject *parent) :
    IAssetService(parent)
{
    ICollectionController* collController = ICore::collectionController();
    connect(collController, SIGNAL(newItem(Core::DataItem*)), this, SLOT(getCover(Core::DataItem*)));
}

DataItem::DATA_ITEM_TYPE AlbumCoversAssetService::getAssetType()
{
    return DataItem::ALBUM;
}

void AlbumCoversAssetService::updateCovers()
{

    ICollectionController* collController = ICore::collectionController();

    // get Collections
    QList<IMediaCollection*> list = collController->getCollections("org.safri.collection.audio");
    QList<DataItem*> albumList;

    //collect all Albums
    for (int i = 0; i < list.size(); i++)
    {
        albumList.append(list.at(i)->getDataItems(DataItem::ALBUM));
    }

    //Request Covers
    for(int i=0; i < albumList.size(); i++)
    {
        getCover(albumList.at(i));
    }
}

void AlbumCoversAssetService::getCover(Core::DataItem* item)
{
    Controller::InfoController* controller = ICore::infoController();
    Album* album = qobject_cast<Album*>(item);
    if(album)
    {
        Core::InfoRequest* request = controller->getInfoForItem("org.safri.audio.album.cover", album);
        connect(request, SIGNAL(infoDataAvailable()), this, SLOT(infoSlot()));
    }
    else
    {
        qDebug()<<Q_FUNC_INFO<<" ERROR!";
    }
}


QString AlbumCoversAssetService::getName()
{
    return "DisplayRole";
}

QVariant AlbumCoversAssetService::getAsset(DataItem *item)
{
    if(item && item->getType() == DataItem::ALBUM)
    {
        QString path = item->getMediaCollection()->getAssetFolderPath("AlbumCoversPreview").toString()+"/"+QString::number(item->getID()) + ".jpg";
        QImage cover(path);
        if (cover.isNull())
        {
            cover = QImage(":/icons/ressources/default.png");
        }
        return cover;
    }
}

void AlbumCoversAssetService::infoSlot()
{
    Core::InfoRequest* req = qobject_cast<InfoRequest*>(sender());
    if(req)
    {
        QPixmap pixmap = req->getInfo().value<QPixmap>();
        QImage cover = pixmap.toImage();

        if ( !cover.isNull() )
        {
            DataItem* item = req->getRelatedItem();
            QString path = item->getMediaCollection()->getAssetFolderPath("AlbumCoversPreview").toString()+"/"+QString::number(item->getID()) + ".jpg";

            cover = cover.scaled(43, 43, Qt::IgnoreAspectRatio, Qt::FastTransformation);
            qDebug()<<"Cover saved:"<<cover.save(path, "jpg", 60);
        }
    }
    delete req;
}
