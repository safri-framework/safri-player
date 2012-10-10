#ifndef ICORE_H
#define ICORE_H

#include "CorePlugin_global.h"

#include <QObject>

namespace Core
{
    class IPlaybackController;
    class CorePlugin;

    class COREPLUGINSHARED_EXPORT ICore : public QObject
    {
        Q_OBJECT

        friend class CorePlugin;

        private:

            explicit ICore();

        public:

            static ICore* instance();
            static IPlaybackController* playbackController();
            static void registerPlaybackController(IPlaybackController* pbc);

        public slots:

            void objectAddedToObjectPool(QObject *object);

        private:

            static ICore* m_instance;
            IPlaybackController* m_playbackController;
    };
}

#endif // ICORE_H
