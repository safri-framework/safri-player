#ifndef COVERASSETSERVICE_H
#define COVERASSETSERVICE_H

#include "Interfaces/IAssetService.h"

using namespace Core;
class CoverAssetService : public IAssetService
{
    Q_OBJECT
public:
    explicit CoverAssetService(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // COVERASSETSERVICE_H
