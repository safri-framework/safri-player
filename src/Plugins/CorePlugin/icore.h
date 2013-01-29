#ifndef ICORE_H
#define ICORE_H

#include "CorePlugin_global.h"

#include <QObject>

namespace Plugins { class CorePlugin; }

namespace Core
{
    class IPlaybackController;
    class IMediaBackend;
    class IPlaylistFactory;
    class IPlaylist;
    class IGUIController;
    class ICollectionController;

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
            static IPlaylist* createPlaylist();
            static IGUIController* guiController();
            static ICollectionController* collectionController();
            static QString storageDirectory();

        public slots:

            void objectAddedToObjectPool(QObject *object);

        private:

            static Core::ICore* m_instance;
            IPlaybackController* m_playbackController;
            IMediaBackend* m_audioBackend;
            IPlaylistFactory* m_playlistFactory;
            IGUIController* m_guiController;
            ICollectionController* m_collectionController;
    };
}

#endif // ICORE_H
