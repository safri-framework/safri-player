#ifndef SHOUTCASTSTREAM_H
#define SHOUTCASTSTREAM_H

#include "CoreData/Media.h"

using namespace Core;
class ShoutCastStream : public Media
{
public:
    ShoutCastStream(QString name, QString URL);
    QUrl getURL();
    QString getMimeType();
    QList<Media*> getMedia();

private:
    QUrl url;

};

#endif // SHOUTCASTSTREAM_H
