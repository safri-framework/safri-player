#include "testplugin.h"

#include <QDebug>

#include "pluginmanager.h"

#include "CoreData/genre.h"
#include "iplaybackcontroller.h"
#include "icore.h"
#include "Interfaces/IAudioBackend.h"
#include <QFile>

using namespace Plugins;

TestPlugin::TestPlugin()
{
    qDebug() << "TestPlugin()";
}

TestPlugin::~TestPlugin()
{
    qDebug() << "~TestPlugin";
}

bool TestPlugin::initialize(QStringList __attribute__ ((unused)) &arguments)
{
    qDebug() << "TestPlugin::initialize(...)";

    Core::Genre *genre = new Core::Genre(1, "Rock");

    qDebug() << genre->getName();
    qDebug() << Core::DataItem::typeToString(genre->getType());

    Core::IPlaybackController *pbc;


    QList<Core::IPlaybackController*> objects = PluginSystem::PluginManager::instance()->getObjects<Core::IPlaybackController>();

    qDebug() << objects.size();

    pbc = objects.at(0);
    pbc->getPlaylist();



    pbc = Core::ICore::playbackController();
    pbc->getPlaylist();

    //Core::ICore::audioBackend()->play(QUrl("audacity-test-file.mp3"));
    int totalTime = Core::ICore::audioBackend()->getTotalTime();

    Core::ICore::audioBackend()->setVolume(100);

    qDebug() << QString::number(totalTime / 1000.0f);

    return true;
}

Q_EXPORT_PLUGIN2(TestPlugin, TestPlugin)
