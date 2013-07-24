#include "ViewController.h"
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
#include "Settings/SettingsManager.h"
#include <QModelIndex>
#include <QSharedPointer>
#include "CoreSupply/AssetController.h"
#include "QMainWindow"
#include "QApplication"

ViewController::ViewController(IAppController *appController): appController(appController), model(0), plModel(0)
{
    QQuickView *view = new QQuickView();
    view->setSource(QUrl("qrc:/qml/main.qml"));
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->show();
    QApplication::instance()->installEventFilter(this);

    model = appController->getSongtreeModel();
    proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    proxy->sort(0);
    qDebug()<<model->rowCount();
    context = view->rootContext();
    context->setContextProperty("musicModel", proxy);
    connect(appController, SIGNAL(newPlaylistModel()), this, SLOT(newPlaylistModel()));

    playPauseButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("playStop"));
    nextButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("nextButton"));
    prevButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("prevButton"));
    silentButton = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("silentButton"));
    songTree = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("treeView"));
    dialerView = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("dialerView"));
    musicProgress = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("musicProgress"));
    currentSongDisplay = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("currentSongDisplay"));
    playlistView = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("playList"));
    settingsDialog = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("settingsDialog"));
    menuItemDisconnect = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("menuItemDisconnect"));

    if (menuItemDisconnect == 0)
    {
        qDebug() << "menuItemDisconnect == 0";
    }

    Core::IPlaybackController* controller  = Core::ICore::playbackController();

    connect(controller, SIGNAL(stateChanged(Core::playState)), this, SLOT(stateChanged(Core::playState)));
    connect(playPauseButton, SIGNAL(buttonClicked()), controller->playPauseAction(), SLOT(trigger()));
    connect(nextButton, SIGNAL(buttonClicked()), controller->nextAction(), SLOT(trigger()));
    connect(prevButton, SIGNAL(buttonClicked()), controller->previousAction(), SLOT(trigger()));
    connect(silentButton, SIGNAL(buttonClicked()), this, SLOT(testPlay()));
    connect(dialerView, SIGNAL(volumeChanged(QVariant)), this, SLOT(volumeSlot(QVariant)));
    connect(playlistView, SIGNAL(movePos(QVariant, QVariant)), this, SLOT(changePos(QVariant,QVariant)));
    connect(playlistView, SIGNAL(removeIndexFromPlaylist(QVariant)), this, SLOT(removeFromPlaylist(QVariant)));
    connect(playlistView, SIGNAL(playIndex(QVariant)), this, SLOT(playPlaylistIndex(QVariant)));
    connect(controller, SIGNAL(update(int)), this, SLOT(setMusicProgress(int)));
    connect(controller, SIGNAL(mediaChanged(Core::Media*)), this, SLOT(updateMedia(Core::Media*)));
    connect(settingsDialog, SIGNAL(connectTo(QVariant, QVariant)), this, SLOT(connectTo(QVariant,QVariant)));
    connect(menuItemDisconnect, SIGNAL(disconnect()), this, SLOT(disconnect()));

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
        connect(songTree, SIGNAL(enqueueModelIndex(QVariant)), this, SLOT(enqueueModelIndex(QVariant)));
    }
    else
        qDebug()<<"NIX GEFUNDEN )= ";

    plModel = appController->getPlaylistModel();

    if (plModel != 0)
    {
        context->setContextProperty("playlistModel", plModel);
    }

    stateChanged(controller->getCurrentState());
}

void ViewController::playPauseSlot()
{
    qDebug()<<"PLAY PAUSE";
}

bool ViewController::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        qDebug() << "Ate key press" << keyEvent->key();
        return false;
    }

#ifdef ANDROID
    if(event->type() == QEvent::Close)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        backClicked();
        return true;
    }
    return false;
#endif
}

void ViewController::stateChanged(Core::playState state)
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

void ViewController::playModelIndex(QVariant var)
{
    QModelIndex proxyIndex = var.value<QModelIndex>();
    QModelIndex treeIndex = proxy->mapToSource(proxyIndex);

    appController->playTreeModelIndex(treeIndex);
/*TMP
    QAbstractItemModel* playlistModel = appController->getPlaylistModel();
    if (playlistModel)
    {
        context->setContextProperty("playlistModel", playlistModel);
    }
*/
}

void ViewController::enqueueModelIndex(QVariant var)
{
    QModelIndex proxyIndex = var.value<QModelIndex>();
    QModelIndex treeIndex = proxy->mapToSource(proxyIndex);
    appController->enqueueTreeModelIndex(treeIndex);
}

void ViewController::testPlay()
{

}

void ViewController::volumeSlot(QVariant vol)
{
        IPlaybackController* playbackController = Core::ICore::playbackController();
        playbackController->setVolume(vol.toInt());
}

void ViewController::setMusicProgress(int val)
{
    QMetaObject::invokeMethod(musicProgress, "setProgress",
                              Q_ARG(QVariant, Core::ICore::playbackController()->getMediaTotalTime()), Q_ARG(QVariant, val));
}

void ViewController::updateMedia(Media *media)
{
    Core::Song* song = qobject_cast<Core::Song*>(media);
    if(song)
    {
        QString coverPath;

        coverPath = ICore::instance()->assetController()->getAsset("CoverURL", song->getAlbum()).toString();
        if(coverPath != "")
            coverPath = "file://" + coverPath;
        qDebug()<<"PATH "+coverPath;

        setMusicProgress(0);

        QMetaObject::invokeMethod(currentSongDisplay, "newSong",
                                  Q_ARG(QVariant, song->getName()), Q_ARG(QVariant, song->getArtist()->getName()),  Q_ARG(QVariant, song->getAlbum()->getName()),  Q_ARG(QVariant, coverPath));

    }
}

void ViewController::changePos(QVariant from, QVariant to)
{
    //playList->moveMedia(from.toInt(), to.toInt());
    appController->moveMediaInPlaylist(from.toInt(), to.toInt());
}

void ViewController::removeFromPlaylist(QVariant index)
{
    appController->removeIndexFromPlaylist(index.toInt());
}

void ViewController::backClicked()
{
    QMetaObject::invokeMethod(songTree, "prevIndex");
}

void ViewController::playPlaylistIndex(QVariant index)
{
    qDebug()<<"APP INSTANCE PLAY "<<index.toInt();
    appController->playPlaylistIndex(index.toInt());

}

void ViewController::newPlaylistModel()
{
    qDebug()<<"NEW PLAYLIST";
    QAbstractItemModel* playlistModel = appController->getPlaylistModel();
    if (playlistModel)
    {
        context->setContextProperty("playlistModel", playlistModel);
    }
}

void ViewController::connectTo(QVariant host, QVariant port)
{
    /*
    qDebug() << "SETTINGS CHANGED: " << host.toString() << " / " << port.toString() ;

    Core::SettingsModule *restSettings = Core::ICore::settingsManager()->getModule("org.safri.restapi");

    restSettings->setSetting("host", host);
    restSettings->setSetting("port", port);

    Core::ICore::settingsManager()->saveSettings();
    */

    Q_EMIT requestConnect(host.toString(), port.toInt());
}

void ViewController::disconnect()
{
    qDebug() << "ViewController::disconnect()";
    Q_EMIT disconnect();
}
