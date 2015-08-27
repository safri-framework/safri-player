#ifndef MEDIAINFOCONTAINERLIST_H
#define MEDIAINFOCONTAINERLIST_H

#include <QObject>
#include "MediaInfoContainer.h"
#include "../CorePlugin_global.h"


namespace Core
{
    class COREPLUGINSHARED_EXPORT MediaInfoContainerList : public QObject
    {
        Q_OBJECT

    public:
        explicit MediaInfoContainerList(QObject *parent = 0);
        void addMediaInfoContainer(MediaInfoContainer container);
        QString toJson();
        bool fromJson(QString json);
        int size();
        MediaInfoContainer getContainerAt(int index);

    private:

        QVariantList _list;

    signals:

    public slots:

};
}

#endif // MEDIAINFOCONTAINERLIST_H
