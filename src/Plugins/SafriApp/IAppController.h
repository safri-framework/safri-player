#ifndef IAPPCONTROLLER_H
#define IAPPCONTROLLER_H

#include <QObject>

class QAbstractItemModel;

class IAppController : public QObject
{
    Q_OBJECT
    public:

        explicit IAppController(QObject *parent = 0);
    
        virtual QAbstractItemModel* getSongtreeModel() = 0;
};

#endif // IAPPCONTROLLER_H
