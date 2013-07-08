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
    IAssetService(parent),
    saveHiresCovers(true)
{
    ICollectionController* collController = ICore::collectionController();
    connect(collController, SIGNAL(newItem(Core::DataItem*)), this, SLOT(getCover(Core::DataItem*)));
}

DataItem::DATA_ITEM_TYPE AlbumCoversAssetService::getSupportedDataType()
{
    return DataItem::ALBUM;
}

void AlbumCoversAssetService::updateCovers(QString res)
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
    if(album && album->getName() != "Unbekannt")
    {
        Core::InfoRequest* request;
        QString infoType;
        if (saveHiresCovers)
            infoType = "org.safri.audio.album.cover.hires";
        else
            infoType = "org.safri.audio.album.cover";

        request = controller->getInfoForItem(infoType, album);
        connect(request, SIGNAL(infoDataAvailable()), this, SLOT(infoSlot()));
    }
}


QStringList AlbumCoversAssetService::getSupportedServices()
{
    QStringList serviceList;
    serviceList.append("DisplayRole");
    serviceList.append("CoverURL");
    return serviceList;
}


QVariant AlbumCoversAssetService::getAsset(DataItem *item, QString service)
{
    if(item && item->getType() == DataItem::ALBUM && service == "DisplayRole")
    {
        QString path = item->getMediaCollection()->getAssetFolderPath("AlbumCoversPreview").toString()+"/"+QString::number(item->getID()) + ".jpg";
        QImage cover(path);
        if (cover.isNull())
        {
            cover = QImage(":/icons/ressources/default.png");
        }
        return cover;
    }
    if(item && item->getType() == DataItem::ALBUM && service == "CoverURL")
    {
        QString path = item->getMediaCollection()->getAssetFolderPath("AlbumCoversHires").toString()+"/"+QString::number(item->getID()) + ".jpg";
        return path;
    }
    return QVariant();
}

void AlbumCoversAssetService::infoSlot()
{
    Core::InfoRequest* req = qobject_cast<InfoRequest*>(sender());
    if(req && req->isInfoAvailable())
    {
        QPixmap pixmap = req->getInfo().value<QPixmap>();
        QImage cover = pixmap.toImage();

        if ( !cover.isNull() )
        {
            DataItem* item = req->getRelatedItem();
            QString path = item->getMediaCollection()->getAssetFolderPath("AlbumCoversPreview").toString()+"/"+QString::number(item->getID()) + ".jpg";
            QString hiresPath = item->getMediaCollection()->getAssetFolderPath("AlbumCoversHires").toString()+"/"+QString::number(item->getID()) + ".jpg";
            if(saveHiresCovers)
                cover.save(hiresPath, "jpg", 60);
            cover = cover.scaled(43, 43, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            cover.save(path, "jpg", 60);
        }
    }
    delete req;
}
