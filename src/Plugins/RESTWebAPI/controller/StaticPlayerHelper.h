#ifndef STATICPLAYERHELPER_H
#define STATICPLAYERHELPER_H

#include "CoreData/media.h"
#include <QJsonObject>
#include <QObject>

class StaticPlayerHelper : public QObject
{
    Q_OBJECT

public:

    StaticPlayerHelper();
    static QJsonObject getStatus();
    static QJsonObject getMedia(Core::Media* media);
};

#endif // STATICPLAYERHELPER_H
