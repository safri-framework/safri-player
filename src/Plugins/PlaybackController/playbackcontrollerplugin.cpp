#include "playbackcontrollerplugin.h"
#include <QDebug>

PlaybackControllerPlugin::PlaybackControllerPlugin()
{
}

PlaybackControllerPlugin::~PlaybackControllerPlugin()
{
}

bool PlaybackControllerPlugin::initialize(QStringList &arguments)
{
    qDebug() << "PlaybackControllerPlugin::initialize()";

    return true;
}

Q_EXPORT_PLUGIN2(PlaybackControllerPlugin, PlaybackControllerPlugin)
