#ifndef ALBUMCOVERSASSETSERVICE_H
#define ALBUMCOVERSASSETSERVICE_H

#include "Interfaces/IAssetService.h"


using namespace Core;
class AlbumCoversAssetService : public IAssetService
{
    Q_OBJECT
public:
    explicit                    AlbumCoversAssetService(QObject *parent = 0);
    virtual QVariant            getAsset(DataItem *item, QString service);
    virtual QStringList         getSupportedServices();

    DataItem::DATA_ITEM_TYPE    getSupportedDataType();

public slots:
    void                        updateCovers(QString res = "");
    void                        getCover(Core::DataItem* item);

private slots:
    void                        infoSlot();

private:
   bool saveHiresCovers;
   bool overwriteCovers;


signals:

public slots:

};

#endif // ALBUMCOVERSASSETSERVICE_H
