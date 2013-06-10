#include "IAssetService.h"

using namespace Core;
IAssetService::IAssetService(QObject *parent) :
    QObject(parent)
{
}

DataItem::DATA_ITEM_TYPE IAssetService::getSupportedDataType()
{
    return DataItem::NONE;
}
