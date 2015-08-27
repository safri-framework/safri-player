#include "SpotifySafriHelper.h"


SpotifySafriHelper* SpotifySafriHelper::m_instance = 0;


SpotifySafriHelper *SpotifySafriHelper::instance()
{
    if(!m_instance)
        m_instance = new SpotifySafriHelper();

    return m_instance;
}

bool SpotifySafriHelper::appendToCurrentPlaylist(QString mediaInfoContainer)
{
    QSharedPointer<Core::IPlaylist> pl = Core::ICore::playbackController()->getPlaylist();
    if(pl.isNull())
        return false;

    MediaInfoContainerList list;
    list.fromJson(mediaInfoContainer);
    for(int i = 0; i < list.size();i++)
    {
        MediaInfoContainer container = list.getContainerAt(i);
        pl->appendMedia(m_collection->addMedia(container));
    }
    return true;
}

SpotifySafriHelper::SpotifySafriHelper(QWidget *parent) :
    QObject(parent),
    m_collection(ICore::createMediaCollection("org.safri.collection.audio","tmp"))
{
}
