#ifndef MEDIAINFOCONTAINER_H
#define MEDIAINFOCONTAINER_H

#include <QObject>
#include "../CorePlugin_global.h"
#include <QUrl>
#include <QMap>

namespace Core
{

    enum MediaInfoType
    {
        MimeType = 1,
        Artist,
        Album,
        Genre,
        Title,
        Track,
        Length,
        Year,
        FileSize,
        BitRate
    };

    class COREPLUGINSHARED_EXPORT MediaInfoContainer : public QObject
    {
        Q_OBJECT
        public:

            explicit MediaInfoContainer(QUrl mediaUrl, QObject *parent = 0);

            void setMediaInfo(MediaInfoType type, QString info);
            QString getMediaInfo(MediaInfoType type);

        private:

            QUrl mediaUrl;
            QMap<MediaInfoType, QString> infoMap;
    };
}

#endif // MEDIAINFOCONTAINER_H
