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

    class COREPLUGINSHARED_EXPORT MediaInfoContainer
    {
        public:

        explicit MediaInfoContainer(QUrl mediaUrl = QUrl());

            void setMediaInfo(MediaInfoType type, QVariant info);
            QVariant getMediaInfo(MediaInfoType type);

        private:

            QUrl mediaUrl;
            QMap<MediaInfoType, QVariant> infoMap;
    };
}

#endif // MEDIAINFOCONTAINER_H
