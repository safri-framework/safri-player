#include "IMediaCollection.h"
#include "IMediaTagger.h"
#include <QThread>

using namespace Core;

IMediaCollection::IMediaCollection(QObject *parent)
    : QObject(parent)
{
}

IMediaCollection::~IMediaCollection()
{
}
