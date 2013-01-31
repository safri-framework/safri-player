#include "playbackcontrollerplugin.h"
#include <QDebug>

#include "playbackcontroller.h"

using namespace Plugins;

PlaybackControllerPlugin::PlaybackControllerPlugin()
{
}

PlaybackControllerPlugin::~PlaybackControllerPlugin()
{
}

bool PlaybackControllerPlugin::initialize(QStringList &arguments)
{
    Q_UNUSED(arguments)
    qDebug() << "PlaybackControllerPlugin::initialize()";

    PlaybackController *pbc = new PlaybackController();

    addObject(pbc);

    return true;
}

Q_EXPORT_PLUGIN2(PlaybackControllerPlugin, PlaybackControllerPlugin)
