#ifndef MEDIAINFOCONTAINER_H
#define MEDIAINFOCONTAINER_H

#include <QObject>
#include "../CorePlugin_global.h"
#include <QUrl>
#include <QMap>
#include <QVariant>

namespace Core
{

    enum MediaInfoType
    {
        InfoMimeType = 1,
        InfoArtist,
        InfoAlbum,
        InfoGenre,
        InfoTitle,
        InfoTrack,
        InfoLength,
        InfoYear,
        InfoFileSize,
        InfoBitRate,
        InfoURL
    };

    class COREPLUGINSHARED_EXPORT MediaInfoContainer : public QObject
    {
        Q_OBJECT
        public:

        explicit MediaInfoContainer(QUrl mediaUrl, QObject *parent = 0);

            void setMediaInfo(MediaInfoType type, QVariant info);
            QVariant getMediaInfo(MediaInfoType type);

        private:

            QUrl mediaUrl;
            QMap<MediaInfoType, QVariant> infoMap;
    };
}

#endif // MEDIAINFOCONTAINER_H
