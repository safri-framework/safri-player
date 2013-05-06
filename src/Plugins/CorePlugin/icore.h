#ifndef ICORE_H
#define ICORE_H

#include "CorePlugin_global.h"

#include <QObject>
#include <QMap>
#include <QSharedPointer>


namespace Plugins { class CorePlugin; }
namespace Controller { class InfoController; }

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
    class IMediaCollection;
    class IMediaCollectionFactory;
    class SettingsManager;

    class COREPLUGINSHARED_EXPORT ICore : public QObject
    {
        Q_OBJECT

        friend class Plugins::CorePlugin;

        private:

            explicit ICore();

        public:

            static ICore*                       instance();
            static Controller::InfoController*  infoController();
            static SettingsManager*             settingsManager();
            static IPlaybackController*         playbackController();
            static IMediaBackend*               audioBackend();
            static QSharedPointer<IPlaylist>    createPlaylist();
            static IGUIController*              guiController();
            static ICollectionController*       collectionController();
            static QString                      storageDirectory();
            static IMediaBackend*               getBackendForMedia(Media* media);
            static IMediaBackend*               getBackendForMimeType(QString mimeType);
            static IMediaCollection*            createMediaCollection(QString type, QString collectionName);


        private slots:

            void objectAddedToObjectPool(QObject *object);

        private:

            static Core::ICore* m_instance;
            IPlaybackController* m_playbackController;
            IMediaBackend* m_audioBackend;
            IPlaylistFactory* m_playlistFactory;
            IGUIController* m_guiController;
            Controller::InfoController*  m_infoController;
            ICollectionController* m_collectionController;
            SettingsManager* m_settingsManager;
            QMap<QString, IMediaBackend*> m_mediaBackends;
            QMap<QString, IMediaCollectionFactory*> m_collectionFactories;
    };
}

#endif // ICORE_H
