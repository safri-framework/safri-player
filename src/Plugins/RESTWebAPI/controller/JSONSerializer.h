#ifndef STATICPLAYERHELPER_H
#define STATICPLAYERHELPER_H

#include "CoreData/Media.h"
#include <QJsonObject>
#include <QObject>
#include <Songtree/SongTreeItem.h>

namespace Core
{
    class IPlaybackController;
}


class JSONSerializer : public QObject
{
    Q_OBJECT
    public:

        JSONSerializer();
        static QJsonObject getStatus();
        static QJsonObject getMedia(Core::DataItem* media);
        static QJsonObject getSongTreeItemForJsTree(Core::SongTreeItem* item, int id);
        static QJsonObject generateErrorObject(QString errorMsg, QString function, bool ok);

    private:

        static QString getCurrentState(Core::IPlaybackController* playbackController);
};

#endif // STATICPLAYERHELPER_H
