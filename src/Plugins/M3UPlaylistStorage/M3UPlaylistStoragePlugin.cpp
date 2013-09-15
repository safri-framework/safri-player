#include "M3UPlaylistStoragePlugin.h"
#include <QDebug>

#include "M3UPlaylistStorage.h"

using namespace Plugins;

M3UPlaylistStoragePlugin::M3UPlaylistStoragePlugin()
{
}

bool M3UPlaylistStoragePlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    qDebug() << "M3U Playlist storage";

    addObject( new M3UPlaylistStorage() );

    return true;
}
