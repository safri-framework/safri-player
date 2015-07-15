#include "AlbumCoversAssetService.h"
#include "Interfaces/IMediaCollection.h"
#include "CoreData/Album.h"
#include "Interfaces/ICollectionController.h"
#include "CoreSupply/InfoController.h"
#include "CoreSupply/InfoRequest.h"
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QImage>
#include "Interfaces/ICore.h"
#include <QFile>
#include <Interfaces/ISafriSkin.h>
#include <QIcon>

AlbumCoversAssetService::AlbumCoversAssetService(QObject *parent) :
    IAssetService(parent),
    saveHiresCovers(true),
    overwriteCovers(false),
    noCoverCover(0)
{
    ICollectionController* collController = ICore::collectionController();
    connect(collController, SIGNAL(newItem(Core::DataItem*)), this, SLOT(getCover(Core::DataItem*)));
    ISafriSkin* skin = Core::ICore::instance()->skin();
    if(skin)
    {
        QIcon* tmp = skin->getIcon("NoCoverCover");
        if(tmp)
          noCoverCover = tmp;
    }
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

    if(!item->getMediaCollection())
        return;

    QString path = item->getMediaCollection()->getAssetFolderPath("AlbumCoversPreview").toString()+"/"+QString::number(item->getID()) + ".jpg";
    if((!QFile::exists(path) ) | overwriteCovers)
    {
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
    else
    {
        qDebug()<<"Cover already exists... (: ";
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
    if (!item->getMediaCollection())
        return QVariant();

    if(item && item->getType() == DataItem::ALBUM && service == "DisplayRole")
    {
        QString path = item->getMediaCollection()->getAssetFolderPath("AlbumCoversPreview").toString()+"/"+QString::number(item->getID()) + ".jpg";
        QImage cover(path);
        if (cover.isNull())
        {
            if(noCoverCover)
                return noCoverCover->pixmap(43,43);
            cover = QImage(":/border_images/Ressources/no_cover.png").scaled(43, 43, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
        return cover;
    }
    if(item && item->getType() == DataItem::ALBUM && service == "CoverURL")
    {
        QString path = item->getMediaCollection()->getAssetFolderPath("AlbumCoversHires").toString()+"/"+QString::number(item->getID()) + ".jpg";
        if(QFile::exists(path))
            return path;
        else
            return "";
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
            qDebug()<<path;
            QString hiresPath = item->getMediaCollection()->getAssetFolderPath("AlbumCoversHires").toString()+"/"+QString::number(item->getID()) + ".jpg";
            if(saveHiresCovers)
                cover.save(hiresPath, "jpg", 60);
            cover = cover.scaled(43, 43, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            cover.save(path, "jpg", 60);
        }
    }
    delete req;
}
