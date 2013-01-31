#ifndef IPLAYLISTFACTORY_H
#define IPLAYLISTFACTORY_H

#include "../CorePlugin_global.h"
#include "../iplaylist.h"
#include <QObject>
#include <QSharedPointer>

namespace Core
{
    class COREPLUGINSHARED_EXPORT IPlaylistFactory : public QObject
    {
        Q_OBJECT
        public:

            virtual QSharedPointer<Core::IPlaylist> createPlaylist() = 0;
    };
}

#endif // IPLAYLISTFACTORY_H
