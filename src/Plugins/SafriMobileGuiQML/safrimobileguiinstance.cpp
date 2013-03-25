#include "safrimobileguiinstance.h"
#include <QDebug>
//#include <QDeclarativeView>
//#include <QDeclarativeItem>
#include <QtQuick/QQuickView>
#include <QQmlContext>
#include <QtWidgets/QAction>
#include "Songtree/CoreItemTypes/artistitemtype.h"
#include "Songtree/CoreItemTypes/albumitemtype.h"
#include "Songtree/CoreItemTypes/songitemtype.h"
#include "Songtree/CoreItemTypes/mediacollectionitemtype.h"
#include "Songtree/CoreItemTypes/genreitemtype.h"

#include "Interfaces/ICollectionController.h"

#include "Interfaces/IStorageAdapter.h"
#include "Interfaces/IPlaylistFactory.h"
#include "Interfaces/IMediaCollectionBuilder.h"

#include "pluginmanager.h"

#include "iplaybackcontroller.h"
#include <QModelIndex>

SafriMobileGuiInstance::SafriMobileGuiInstance():model(0)
{
    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/test/qml/main.qml"));
    view->show();

    test();
    model = getSongtreeModel();


    QQmlContext* context = view->rootContext();
    context->setContextProperty("musicModel", model);

    playPauseButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("playStop"));
    nextButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("nextButton"));
    prevButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("prevButton"));
    silentButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("silentButton"));
    songTree = qobject_cast<QQuickItem*>(view->rootObject());



    Core::IPlaybackController* controller  = Core::ICore::playbackController();



    connect(controller, SIGNAL(stateChanged(Core::playState)), this, SLOT(stateChanged(Core::playState)));
    connect(playPauseButton, SIGNAL(buttonClicked()), controller->playPauseAction(), SLOT(trigger()));
    connect(nextButton, SIGNAL(buttonClicked()), controller->nextAction(), SLOT(trigger()));
    connect(prevButton, SIGNAL(buttonClicked()), controller->previousAction(), SLOT(trigger()));
    connect(silentButton, SIGNAL(buttonClicked()), this, SLOT(testPlay()));

    playPauseButton->setProperty("enabled", false);
    nextButton->setProperty("enabled", false);
    prevButton->setProperty("enabled", false);
 //   silentButton->setProperty("enabled", false);

    if(songTree)
    {

        connect(songTree, SIGNAL(play(QVariant)), this, SLOT(playModelIndex(QVariant)));
    }else
        qDebug()<<"NIX GEFUNDEN )= ";

}

void SafriMobileGuiInstance::playPauseSlot()
{
    qDebug()<<"PLAY PAUSE";
}



void SafriMobileGuiInstance::stateChanged(Core::playState state)
{
    qDebug()<<"STATE"<<state;

    if(state != NODATA)
    {
        playPauseButton->setProperty("enabled", true);
        nextButton->setProperty("enabled", true);
        prevButton->setProperty("enabled", true);
        silentButton->setProperty("enabled", true);
    }
    else
    {
        playPauseButton->setProperty("enabled", false);
        nextButton->setProperty("enabled", false);
        prevButton->setProperty("enabled", false);
        silentButton->setProperty("enabled", false);

    }

    switch(state)
    {
        case PLAY:
        {
            playPauseButton->setProperty("playing", true);
            qDebug()<<"PLAYING";
            break;
        }

        case STOP:
        {
           playPauseButton->setProperty("playing", false);
           qDebug()<<"STOP";
           break;
        }

        case PAUSE:
        {
            playPauseButton->setProperty("playing", false);
            qDebug()<<"PAUSE";
            break;
        }

    }

}

void SafriMobileGuiInstance::playModelIndex(QVariant var)
{
    qDebug()<<var;
    qDebug()<<var.value<QModelIndex>();
    QModelIndex index = var.value<QModelIndex>();
    SongTreeItem* item = static_cast<SongTreeItem*>(index.internalPointer());
    QSharedPointer<Core::IPlaylist> playList = Core::ICore::createPlaylist();
   QList<Core::Item*> items;
   items.append(static_cast<Core::Item*>(item));

    playList->insertMediaAt(0,items);

    IPlaybackController* playbackController = Core::ICore::playbackController();
    playbackController->stopAction()->trigger();
    playbackController->setPlaylist(playList);

    playbackController->playAction()->trigger();
}

void SafriMobileGuiInstance::testPlay()
{

    QSharedPointer<Core::IPlaylist> playList = Core::ICore::createPlaylist();
    Core::Song *testMp31 = new Core::Song(1, "Test", 2012, "qrc:/defaults/testSongs/song1.mp3", this);
    Core::Song *testMp32 = new Core::Song(2, "Test", 2012, "qrc:/defaults/testSongs/song2.mp3", this);

    QList<Core::Item*> songs;
    songs.append(testMp31);
    songs.append(testMp32);




    playList->insertMediaAt(0,songs);

    IPlaybackController* playbackController = Core::ICore::playbackController();
    playbackController->stopAction()->trigger();
    playbackController->setPlaylist(playList);

    playbackController->playAction()->trigger();
}


SongTreeModel *SafriMobileGuiInstance::getSongtreeModel()
{


   ICollectionController* collController = ICore::collectionController();
    QList<IMediaCollection*> mediaColl = collController->getCollections("org.safri.collection.audio");
    for (int i = 0; i < mediaColl.size(); i++)
    {
        IAudioCollection* tempAudioColl = qobject_cast<IAudioCollection*>(mediaColl.at(i));
        if(tempAudioColl)
        {
            audioCollMap.insert(tempAudioColl->getDatabaseLocation(), tempAudioColl);
        }
    }
    QList<IAudioCollection*> audioCollList = audioCollMap.values();
    for(int i = 0 ; i < audioCollList.size(); i++)
    {

        songList.append(audioCollList.at(i)->getSongs());
    }

    tree = new SongTree(songList, treeHierarchy);

    for(int i = 0 ; i < audioCollList.size(); i++)
    {
        qDebug() << "CONNECT itemAdded";
        connect(audioCollList.at(i), SIGNAL(itemAdded(Core::DataItem*)), tree, SLOT(addItem(Core::DataItem*)));
    }
    return new SongTreeModel(tree, this);

}

void SafriMobileGuiInstance::test()
{
     treeHierarchy = new QList<ITreeItemType*>();
     treeHierarchy->append(new MediaCollectionItemType());
     treeHierarchy->append(new GenreItemType());
     treeHierarchy->append(new ArtistItemType());
     treeHierarchy->append(new AlbumItemType());
     treeHierarchy->append(new SongItemType());
}

