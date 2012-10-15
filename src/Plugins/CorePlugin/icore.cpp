#include "icore.h"
#include "pluginmanager.h"
#include "iplaybackcontroller.h"

#include <QDebug>

using namespace Core;

ICore* ICore::m_instance;

ICore::ICore()
{
    qDebug() << "ICore()";
    connect(PluginSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)), this, SLOT(objectAddedToObjectPool(QObject*)));
}

ICore *ICore::instance()
{
    return m_instance;
}

IPlaybackController* ICore::playbackController()
{
    return m_instance->m_playbackController;
}

IAudioBackend *ICore::audioBackend()
{
    return m_instance->m_audioBackend;
}

void ICore::objectAddedToObjectPool(QObject *object)
{
    IPlaybackController *pbc = qobject_cast<IPlaybackController*>(object);
    if (pbc != 0)
    {
        qDebug() << "IPlaybackController class added";
        m_playbackController = pbc;
    }

}


