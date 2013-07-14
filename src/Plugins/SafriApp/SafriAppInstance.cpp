#include "SafriAppInstance.h"
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
#include "Interfaces/IPlaylistFactory.h"
#include "pluginmanager.h"
#include "iplaybackcontroller.h"
#include <QModelIndex>
#include <QSharedPointer>
#include "CoreSupply/AssetController.h"


SafriAppInstance::SafriAppInstance(IAppController *appController): appController(appController), model(0), plModel(0)
{
    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/qml/main.qml"));
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->show();

    model = appController->getSongtreeModel();
    proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    proxy->sort(0);
    qDebug()<<model->rowCount();
    context = view->rootContext();
    context->setContextProperty("musicModel", proxy);

    playPauseButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("playStop"));
    nextButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("nextButton"));
    prevButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("prevButton"));
    silentButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("silentButton"));
    songTree = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("treeView"));
    dialerView = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("dialerView"));
    musicProgress = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("musicProgress"));
    currentSongDisplay = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("currentSongDisplay"));
    playlistView = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("playList"));

    Core::IPlaybackController* controller  = Core::ICore::playbackController();

    connect(controller, SIGNAL(stateChanged(Core::playState)), this, SLOT(stateChanged(Core::playState)));
    connect(playPauseButton, SIGNAL(buttonClicked()), controller->playPauseAction(), SLOT(trigger()));
    connect(nextButton, SIGNAL(buttonClicked()), controller->nextAction(), SLOT(trigger()));
    connect(prevButton, SIGNAL(buttonClicked()), controller->previousAction(), SLOT(trigger()));
    connect(silentButton, SIGNAL(buttonClicked()), this, SLOT(testPlay()));
    connect(dialerView, SIGNAL(volumeChanged(QVariant)), this, SLOT(volumeSlot(QVariant)));
    connect(playlistView, SIGNAL(movePos(QVariant, QVariant)), this, SLOT(changePos(QVariant,QVariant)));

    connect(controller, SIGNAL(update(int)), this, SLOT(setMusicProgress(int)));
    connect(controller, SIGNAL(mediaChanged(Core::Media*)), this, SLOT(updateMedia(Core::Media*)));

    playPauseButton->setProperty("enabled", false);
    nextButton->setProperty("enabled", false);
    prevButton->setProperty("enabled", false);
 //   silentButton->setProperty("enabled", false);
    if(!dialerView)
    {
        "GIBS NET";
    }

    if(songTree)
    {
        connect(songTree, SIGNAL(playModelIndex(QVariant)), this, SLOT(playModelIndex(QVariant)));
    }
    else
        qDebug()<<"NIX GEFUNDEN )= ";
}

void SafriAppInstance::playPauseSlot()
{
    qDebug()<<"PLAY PAUSE";
}

void SafriAppInstance::stateChanged(Core::playState state)
{
    qDebug()<<"STATE"<<state;
    Core::IPlaybackController* controller  = Core::ICore::playbackController();

    if(state != NODATA)
    {
        playPauseButton->setProperty("enabled", true);
        nextButton->setProperty("enabled", true);
        prevButton->setProperty("enabled", true);
       // silentButton->setProperty("enabled", true);
    }

    switch(state)
    {
        case NODATA:
        {
            playPauseButton->setProperty("enabled", false);
            nextButton->setProperty("enabled", false);
            prevButton->setProperty("enabled", false);
          //  silentButton->setProperty("enabled", false);
        }

        case PLAY:
        {
            playPauseButton->setProperty("playing", true);
            currentSongLength = controller->getMediaTotalTime();
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

void SafriAppInstance::playModelIndex(QVariant var)
{
    qDebug()<<var;
    qDebug()<<var.value<QModelIndex>();
    QModelIndex proxyIndex = var.value<QModelIndex>();
    QModelIndex index = proxy->mapToSource(proxyIndex);
    SongTreeItem* item = static_cast<SongTreeItem*>(index.internalPointer());
    playList = Core::ICore::createPlaylist();
    QList<Core::Item*> items;
    items.append(static_cast<Core::Item*>(item));

    playList->insertMediaAt(0,items);
    IPlaybackController* playbackController = Core::ICore::playbackController();
    playbackController->stopAction()->trigger();
    playbackController->setPlaylist(playList);

    playbackController->playAction()->trigger();
    PlaylistModel* oldModel = plModel;

    plModel = new PlaylistModel(playList, this);
    context->setContextProperty("playlistModel", plModel);
    if(oldModel)
        delete oldModel;
}

void SafriAppInstance::testPlay()
{

}

void SafriAppInstance::volumeSlot(QVariant vol)
{
        IPlaybackController* playbackController = Core::ICore::playbackController();
        playbackController->setVolume(vol.toInt());
}

void SafriAppInstance::setMusicProgress(int val)
{
    QMetaObject::invokeMethod(musicProgress, "setProgress",
                              Q_ARG(QVariant, currentSongLength), Q_ARG(QVariant, val));
}

void SafriAppInstance::updateMedia(Media *media)
{
    Core::Song* song = qobject_cast<Core::Song*>(media);
    if(song)
    {
        QMetaObject::invokeMethod(currentSongDisplay, "newSong",
                                  Q_ARG(QVariant, song->getName()), Q_ARG(QVariant, song->getArtist()->getName()),  Q_ARG(QVariant, song->getAlbum()->getName()),  Q_ARG(QVariant, ""));
    }
}

void SafriAppInstance::changePos(QVariant from, QVariant to)
{
    playList->moveMedia(from.toInt(), to.toInt());
}

void SafriAppInstance::removeFromPlaylist(QVariant index)
{
    playList->deleteMedia(index.toInt());
}
