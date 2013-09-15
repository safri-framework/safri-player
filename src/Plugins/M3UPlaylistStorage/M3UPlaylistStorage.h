#ifndef M3UPLAYLISTSTORAGE_H
#define M3UPLAYLISTSTORAGE_H

#include "Interfaces/IPlaylistStorage.h"

class M3UPlaylistStorage : public Core::IPlaylistStorage
{
    Q_OBJECT
    public:

        explicit M3UPlaylistStorage(QObject *parent = 0);

        virtual QString                             getDescription();
        virtual QString                             getFileExtension();

        virtual QSharedPointer<Core::IPlaylist>     loadPlaylist(QString filename);
        virtual bool                                savePlaylist(QString filename, QSharedPointer<Core::IPlaylist> playlist);

};

#endif // M3UPLAYLISTSTORAGE_H
