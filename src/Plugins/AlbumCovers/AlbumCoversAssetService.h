#ifndef ALBUMCOVERSASSETSERVICE_H
#define ALBUMCOVERSASSETSERVICE_H

#include "Interfaces/IAssetService.h"


using namespace Core;
class AlbumCoversAssetService : public IAssetService
{
    Q_OBJECT
public:
    explicit AlbumCoversAssetService(QObject *parent = 0);
    virtual QVariant getAsset(Core::DataItem* item);
    virtual QString getName();

    DataItem::DATA_ITEM_TYPE getAssetType();

public slots:
    void updateCovers();
    void getCover(Core::DataItem* item);

private slots:
    void infoSlot();
    
    
signals:
    
public slots:
    
};

#endif // ALBUMCOVERSASSETSERVICE_H
