#include "icore.h"

using namespace Core;

ICore* ICore::m_instance;

ICore::ICore()
{
}

ICore *ICore::instance()
{
    return m_instance;
}

IPlaybackController *ICore::playbackController()
{
    return m_instance->m_playbackController;
}

void ICore::registerPlaybackController(IPlaybackController *pbc)
{
    m_instance->m_playbackController = pbc;
}


