#ifndef IPLAYLISTSTORAGE_H
#define IPLAYLISTSTORAGE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "CorePlugin_global.h"

#include "IPlaylist.h"
#include <QSharedPointer>

namespace Core
{
    class COREPLUGINSHARED_EXPORT IPlaylistStorage : public QObject
    {
        Q_OBJECT
        public:

            explicit IPlaylistStorage(QObject *parent = 0);

            virtual QString                     getDescription() = 0;
            virtual QString                     getFileExtension() = 0;

            virtual QSharedPointer<IPlaylist>   loadPlaylist(QString filename) = 0;
            virtual bool                        savePlaylist(QString filename, QSharedPointer<IPlaylist> playlist) = 0;
    };
}

#endif // IPLAYLISTSTORAGE_H
