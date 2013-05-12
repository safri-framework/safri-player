#ifndef STATICPLAYERHELPER_H
#define STATICPLAYERHELPER_H

#include "CoreData/media.h"
#include <QJsonObject>
#include <QObject>
#include <Songtree/songtreeitem.h>

class JSONSerializer : public QObject
{
    Q_OBJECT

public:

    JSONSerializer();
    static QJsonObject getStatus();
    static QJsonObject getMedia(Core::DataItem* media);
    static QJsonObject getSongTreeItemForJsTree(Core::SongTreeItem* item, int id);
    static QJsonObject generateErrorObject(QString errorMsg, QString function, bool ok);
};

#endif // STATICPLAYERHELPER_H
