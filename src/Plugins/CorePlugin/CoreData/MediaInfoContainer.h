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
        InfoAlbumArtist,
        InfoAlbum,
        InfoGenre,
        InfoTitle,
        InfoTrack,
        InfoLength,
        InfoYear,
        InfoFileSize,
        InfoBitRate,
        InfoURL,
        InfoMime,
        InfoTemporary
    };

    class COREPLUGINSHARED_EXPORT MediaInfoContainer : public QObject
    {
        Q_OBJECT
        public:

            explicit MediaInfoContainer(QUrl mediaUrl = QUrl(), QObject* parent = 0);
            MediaInfoContainer(MediaInfoContainer &other);

            void setMediaInfo(MediaInfoType type, QVariant info);
            QVariant getMediaInfo(MediaInfoType type);
            QUrl getURL();

        private:

            QUrl mediaUrl;
            QMap<MediaInfoType, QVariant> infoMap;
    };
}

#endif // MEDIAINFOCONTAINER_H
