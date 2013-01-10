#ifndef IPLAYLISTFACTORY_H
#define IPLAYLISTFACTORY_H

#include "../CorePlugin_global.h"
#include "../iplaylist.h"
#include <QObject>

namespace Core
{
    class COREPLUGINSHARED_EXPORT IPlaylistFactory : public QObject
    {
        Q_OBJECT
        public:

            virtual Core::IPlaylist* createPlaylist() = 0;
    };
}

#endif // IPLAYLISTFACTORY_H
