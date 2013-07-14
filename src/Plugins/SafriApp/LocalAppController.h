#ifndef LOCALAPPCONTROLLER_H
#define LOCALAPPCONTROLLER_H

#include "IAppController.h"

namespace Core
{
    class SongTree;
    class ITreeItemType;
}

class LocalAppController : public IAppController
{
    Q_OBJECT
    public:

        explicit LocalAppController(QObject *parent = 0);

        virtual QAbstractItemModel* getSongtreeModel();

    private:

        Core::SongTree* songTree;
        QList<Core::ITreeItemType*>* createTreeHierachy();

    
};

#endif // LOCALAPPCONTROLLER_H
