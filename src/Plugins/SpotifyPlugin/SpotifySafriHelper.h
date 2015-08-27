#ifndef SPOTIFYSAFRIHELPER_H
#define SPOTIFYSAFRIHELPER_H

#include "Interfaces/IPlaybackController.h"
#include "Interfaces/IAudioCollection.h"
#include "CoreData/MediaInfoContainerList.h"
#include "Interfaces/ICore.h"
#include "Interfaces/IPlaylist.h"
#include <QObject>

using namespace Core;

class SpotifySafriHelper : public QObject
{
    Q_OBJECT

public:
    static SpotifySafriHelper* instance();
    bool appendToCurrentPlaylist(QString mediaInfoContainer);

signals:

public slots:

private:
    IMediaCollection* m_collection;
    explicit SpotifySafriHelper(QWidget *parent = 0);
    static SpotifySafriHelper* m_instance;

};

#endif // SPOTIFYSAFRIHELPER_H
