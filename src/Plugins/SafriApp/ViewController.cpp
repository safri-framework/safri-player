#include "ViewController.h"
#include <QDebug>
//#include <QDeclarativeView>
//#include <QDeclarativeItem>

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
#include <QStandardPaths>


ViewController::ViewController(IAppController *appController, QObject* parent): QObject(parent),
    appController(appController),
    model(0),
    plModel(0),
    signalConnectionsInitialized(false),
    view(0),
    isInitialized(false),
    dialogController(0)
{
    view = new QQuickView();
    connect(view, SIGNAL(statusChanged(QQuickView::Status)), this, SLOT(QMLStatusChanged(QQuickView::Status)));
    view->setSource(QUrl("qrc:/qml/main.qml"));
    view->setResizeMode(QQuickView::SizeRootObjectToView);   
    view->show();
    QApplication::instance()->installEventFilter(this);
}

void ViewController::playPauseSlot()
{
    qDebug()<<"PLAY PAUSE";
}

bool ViewController::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)
    switch ( event->type() )
    {
        case QEvent::KeyPress:

            //QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            //qDebug() << "Ate key press" << keyEvent->key();

            break;

        case QEvent::Close:

            #ifdef ANDROID
                backClicked();
                return true;
            #endif

            break;

        default:

            break;
    }

    return false;
}

void ViewController::stateChanged(Core::playState state)
{
    Core::IPlaybackController* controller  = Core::ICore::playbackController();

    if(state != NODATA)
    {
        playPauseButton->setProperty("enabled", true);
        nextButton->setProperty("enabled", true);
        prevButton->setProperty("enabled", true);
    }

    switch(state)
    {
        case NODATA:

            playPauseButton->setProperty("enabled", false);
            nextButton->setProperty("enabled", false);
            prevButton->setProperty("enabled", false);

            break;

        case PLAY:

            playPauseButton->setProperty("playing", true);
            currentSongLength = controller->getMediaTotalTime();
            //qDebug()<<"PLAYING";
            break;


        case STOP:

           playPauseButton->setProperty("playing", false);
           //qDebug()<<"STOP";
           break;


        case PAUSE:

            playPauseButton->setProperty("playing", false);
            //qDebug()<<"PAUSE";
            break;

        default:

            break;
    }

}

void ViewController::playModelIndex(QVariant var)
{
    QModelIndex proxyIndex = var.value<QModelIndex>();
    QModelIndex treeIndex = proxy->mapToSource(proxyIndex);

    appController->playTreeModelIndex(treeIndex);

    // pbcontroller will emit a signal which will reset the playlistmodel
}

void ViewController::enqueueModelIndex(QVariant var)
{

    QModelIndex proxyIndex = var.value<QModelIndex>();
    QModelIndex treeIndex = proxy->mapToSource(proxyIndex);
    appController->enqueueTreeModelIndex(treeIndex);

    qDebug()<<"Append Model Index";
}

void ViewController::testPlay()
{

}


void ViewController::volumeSlot(QVariant vol)
{
        float diff = vol.toFloat();
        if(abs(tmpVolDiff - diff) > 20)
            return;

        tmpVolDiff = diff;
        currentVol += diff/2;

        if (currentVol > 100)
            currentVol =100;
        if (currentVol < 0)
            currentVol = 0;

        Core::ICore::playbackController()->setVolume(currentVol);
        volumeIndicator->setProperty("volume", currentVol);
}

void ViewController::setMusicProgress(int val)
{
    int mediaTotalTime = Core::ICore::playbackController()->getMediaTotalTime();

    if (mediaTotalTime < 0)
    {
        // mediaTotalTime 0 will cause a zero division, by computing the
        // progress percentage, hence we will set it to 1 ms
        // because the display shows seconds, this will be no problem
        // and the intented total time of 0 seconds will be shown
        mediaTotalTime = 1;
    }

    QMetaObject::invokeMethod(musicProgress, "setProgress",
                              Q_ARG(QVariant, mediaTotalTime), Q_ARG(QVariant, val));
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
    else
    {
        setMusicProgress(0);
        QMetaObject::invokeMethod(currentSongDisplay, "newSong",
                                  Q_ARG(QVariant, ""), Q_ARG(QVariant, ""),  Q_ARG(QVariant, ""),  Q_ARG(QVariant, ""));

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
    QMetaObject::invokeMethod(songTreeView, "prevIndex");
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

void ViewController::shuffleClicked()
{
    qDebug()<<"TEST SHUFFLE CLICKED!!";
    qDebug()<<shuffleButton->property("enabled").toBool();
    appController->setShuffle(shuffleButton->property("enabled").toBool());
}

void ViewController::connectTo(QVariant host, QVariant port)
{
    Q_EMIT requestConnect(host.toString(), port.toInt());
}

void ViewController::disconnect()
{
    Q_EMIT requestDisconnect();
}

void ViewController::changeAppController(IAppController *newController)
{

    if (signalConnectionsInitialized)
    {
        QObject::disconnect(playbackController_StateChanged);
        QObject::disconnect(playbackController_Update);
        QObject::disconnect(playbackController_MediaChanged);

        QObject::disconnect(playbackController_playPauseAction);
        QObject::disconnect(playbackController_nextAction);
        QObject::disconnect(playbackController_previousAction);
        QObject::disconnect(playbackController_volChanged);
    }

    appController = newController;

    switch ( appController->getMode() )
    {
        case IAppController::LOCAL:

            QMetaObject::invokeMethod(playerPanel, "setOnlineIndicator", Q_ARG(QVariant, false) );
            break;

        case IAppController::REST:

            QMetaObject::invokeMethod(playerPanel, "setOnlineIndicator", Q_ARG(QVariant, true) );
            break;

        default:
            break;
    }

    connect(appController, SIGNAL(newPlaylistModel()), this, SLOT(newPlaylistModel()));

    // reset the view song display, the correct new values will
    // be set, by the playback controller's mediaChanged signal
    updateMedia(0);

    Core::IPlaybackController* playbackController  = Core::ICore::playbackController();

    playbackController_StateChanged =       connect( playbackController, SIGNAL(stateChanged(Core::playState)), this,   SLOT(stateChanged(Core::playState)));
    playbackController_Update =             connect( playbackController, SIGNAL(update(int)),                   this,   SLOT(setMusicProgress(int)));
    playbackController_MediaChanged =       connect( playbackController, SIGNAL(mediaChanged(Core::Media*)),    this,   SLOT(updateMedia(Core::Media*)));

    playbackController_playPauseAction =    connect( playPauseButton,    SIGNAL(buttonClicked()),   playbackController->playPauseAction(), SLOT(trigger()));
    playbackController_nextAction =         connect( nextButton,         SIGNAL(buttonClicked()),   playbackController->nextAction(),      SLOT(trigger()));
    playbackController_previousAction =     connect( prevButton,         SIGNAL(buttonClicked()),   playbackController->previousAction(),  SLOT(trigger()));
    playbackController_volChanged =         connect( playbackController, SIGNAL(volumeChanged(int)), this, SLOT(volumeChangedByPBController(int)));

    signalConnectionsInitialized = true;

    setupSongtreeModel();

    plModel = appController->getPlaylistModel();

    if (plModel != 0)
    {
        context->setContextProperty("playlistModel", plModel);
    }

    stateChanged(playbackController->getCurrentState());
}

void ViewController::showErrorMessage(QString message)
{
    if(dialogController)
     QMetaObject::invokeMethod(dialogController, "showError", Q_ARG(QVariant, message));
}

void ViewController::setupSongtreeModel(IAppController::TREE_HIERARCHY hierarchy)
{
    model = appController->getSongtreeModel(hierarchy);
    proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    proxy->sort(0);
    context->setContextProperty("musicModel", proxy);
    QMetaObject::invokeMethod(songTreeView, "reset");
}

void ViewController::restSettingsChanged(QString setting)
{
    Core::SettingsModule *restSettings = Core::ICore::settingsManager()->getModule("org.safri.restapi");
    QObject* textField;

    if (setting == "host")
    {
        textField = hostTextField;
    }
    else if (setting == "port")
    {
        textField = portTextField;
    }

    textField->setProperty("text", restSettings->getSetting(setting).toString() );
}

void ViewController::volumeChangedByPBController(int vol)
{
    currentVol = vol;
    volumeIndicator->setProperty("volume", vol);
}

void ViewController::QMLStatusChanged(QQuickView::Status status)
{
    qDebug()<< "STATUS CHANGED;"<<status;
    if(status == QQuickView::Ready && !isInitialized)
    {
        qDebug()<<"READY";
        context = view->rootContext();
        playPauseButton     = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("playStop"));
        nextButton          = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("nextButton"));
        prevButton          = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("prevButton"));
        silentButton        = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("silentButton"));
        songTreeView        = qobject_cast<QQuickItem*>(view->rootObject()->findChild<QQuickItem*>("treeView"));

        dialerView          = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("dialerView"));
        musicProgress       = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("musicProgress"));
        currentSongDisplay  = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("currentSongDisplay"));
        playlistView        = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("playList"));
        settingsDialog      = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("settingsDialog"));
        menuItemDisconnect  = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("menuItemDisconnect"));
        shuffleButton 		= qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("shuffleButton"));
        hostTextField 		= qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("hostTextField"));
        portTextField 		= qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("portTextField"));
        dialogController    = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("dialogController"));
        playerPanel         = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("playerPanel"));
        coverView           = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("coverView"));
        volumeIndicator     = qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("volumeIndicator"));

        genreButton 		= qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("genreButton"));
        artistButton 		= qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("artistButton"));
        albumButton 		= qobject_cast<QObject*>(view->rootObject()->findChild<QObject*>("albumButton"));


        //connect( silentButton,       SIGNAL(buttonClicked()),                    this, SLOT(testPlay())) ;
        connect( dialerView,         SIGNAL(volumeChanged(QVariant)),            this, SLOT(volumeSlot(QVariant)) );
        connect( playlistView,       SIGNAL(movePos(QVariant, QVariant)),        this, SLOT(changePos(QVariant,QVariant)) );
        connect( playlistView,       SIGNAL(removeIndexFromPlaylist(QVariant)),  this, SLOT(removeFromPlaylist(QVariant)) );
        connect( playlistView,       SIGNAL(playIndex(QVariant)),                this, SLOT(playPlaylistIndex(QVariant)) );
        connect( settingsDialog,     SIGNAL(connectTo(QVariant, QVariant)),      this, SLOT(connectTo(QVariant,QVariant)) );
        connect( menuItemDisconnect, SIGNAL(disconnect()),                       this, SLOT(disconnect()) );
        connect( shuffleButton, 	 SIGNAL(buttonClicked()), 					 this, SLOT(shuffleClicked()));
        connect( songTreeView,       SIGNAL(playModelIndexView(QVariant)),       this, SLOT(playModelIndex(QVariant)));
        connect( songTreeView,       SIGNAL(enqueueModelIndexView(QVariant)),    this, SLOT(enqueueModelIndex(QVariant)));
        connect( genreButton,        SIGNAL(buttonClicked()),                    this, SLOT(setGenreTree()));
        connect( artistButton,       SIGNAL(buttonClicked()),                    this, SLOT(setArtistTree()));
        connect( albumButton,        SIGNAL(buttonClicked()),                    this, SLOT(setAlbumTree()));

        playPauseButton->setProperty("enabled", false);
        nextButton->setProperty("enabled", false);
        prevButton->setProperty("enabled", false);

        Core::SettingsModule *restSettings = Core::ICore::settingsManager()->getModule("org.safri.restapi");
        hostTextField->setProperty("text", restSettings->getSetting("host").toString() );
        portTextField->setProperty("text", restSettings->getSetting("port").toString() );



        QString path = QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0)+"/Assets/AlbumCoversHires/";

        qDebug()<<path;
        QString pathII = "file:"+path;
        qDebug()<<pathII<<"  PATH";
        QMetaObject::invokeMethod(coverView, "setFolder",
                                  Q_ARG(QVariant, pathII));
        connect(restSettings, SIGNAL( settingsChanged(QString) ), this, SLOT( restSettingsChanged(QString) ) );

        changeAppController(appController);
        isInitialized = true;
    }
}

void ViewController::setGenreTree()
{
    setupSongtreeModel(IAppController::GENRE);
}

void ViewController::setAlbumTree()
{
    setupSongtreeModel(IAppController::ALBUM);
}

void ViewController::setArtistTree()
{
    setupSongtreeModel(IAppController::ARTIST);
}


