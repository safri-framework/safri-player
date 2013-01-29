#include "IMediaBackend.h"

using namespace Core;

IMediaBackend::IMediaBackend(QObject *parent):QObject(parent)
{

}

int IMediaBackend::getTotalTime()
{
    return -1;
}

int IMediaBackend::getCurrentTime()
{
    return -1;
}

void IMediaBackend::seek(int ms)
{
    Q_UNUSED(ms);
}

void IMediaBackend::pause()
{
}

void IMediaBackend::setVolume(int percent)
{
    Q_UNUSED(percent);
}

int IMediaBackend::getVolume()
{
    return -1;
}


