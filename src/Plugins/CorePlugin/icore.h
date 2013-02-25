#ifndef ICORE_H
#define ICORE_H

#include "CorePlugin_global.h"

#include <QObject>
#include <QMap>
#include <QSharedPointer>


namespace Plugins { class CorePlugin; }

namespace Core
{
    class IPlaybackController;
    class IMediaBackend;
    class IPlaylistFactory;
    class IPlaylist;
    class IGUIController;
    class ICollectionController;
    class IMediaBackend;
    class Media;

    class COREPLUGINSHARED_EXPORT ICore : public QObject
    {
        Q_OBJECT

        friend class Plugins::CorePlugin;

        private:

            explicit ICore();

        public:

            static ICore* instance();
            static IPlaybackController* playbackController();
            static IMediaBackend* audioBackend();
            static QSharedPointer<IPlaylist> createPlaylist();
            static IGUIController* guiController();
            static ICollectionController* collectionController();
            static QString storageDirectory();
            static IMediaBackend* getBackendForMedia(Media* media);
            static IMediaBackend* getBackendForMimeType(QString mimeType);


        private slots:

            void objectAddedToObjectPool(QObject *object);

        private:

            static Core::ICore* m_instance;
            IPlaybackController* m_playbackController;
            IMediaBackend* m_audioBackend;
            IPlaylistFactory* m_playlistFactory;
            IGUIController* m_guiController;
            ICollectionController* m_collectionController;
            QMap<QString, IMediaBackend*> m_mediaBackends;
    };
}

#endif // ICORE_H
