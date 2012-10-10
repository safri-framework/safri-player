#include "playbackcontrollerplugin.h"
#include <QDebug>

#include "playbackcontroller.h"

PlaybackControllerPlugin::PlaybackControllerPlugin()
{
}

PlaybackControllerPlugin::~PlaybackControllerPlugin()
{
}

bool PlaybackControllerPlugin::initialize(QStringList &arguments)
{
    qDebug() << "PlaybackControllerPlugin::initialize()";

    PlaybackController *pbc = new PlaybackController();

    addObject(pbc);

    return true;
}

Q_EXPORT_PLUGIN2(PlaybackControllerPlugin, PlaybackControllerPlugin)
