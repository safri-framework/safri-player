#ifndef MEDIAINFOCONTAINER_H
#define MEDIAINFOCONTAINER_H

#include <QObject>
#include "../CorePlugin_global.h"
#include <QUrl>
#include <QMap>
#include <QVariant>
//#include "MediaInfoContainerList.h"


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
        InfoTemporary,
        NONE
    };

    class COREPLUGINSHARED_EXPORT MediaInfoContainer : public QObject
    {
        friend class MediaInfoContainterList;

        Q_OBJECT

        public:
            explicit MediaInfoContainer(QUrl mediaUrl = QUrl(), QObject* parent = 0);
            MediaInfoContainer(const MediaInfoContainer &other);
            void setMediaInfo(MediaInfoType type, QVariant info);
            QVariant getMediaInfo(MediaInfoType type);
            QUrl getURL();
            QString toJson();
            QVariantMap infoMap;
            static MediaInfoContainer fromJson(QString json);

        private:
           static QString typeToString(MediaInfoType type);
           static MediaInfoType stringToType(QString string);
            QUrl mediaUrl;

    };
}

#endif // MEDIAINFOCONTAINER_H
