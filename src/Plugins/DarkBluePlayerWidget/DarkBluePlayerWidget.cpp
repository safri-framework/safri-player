#include "DarkBluePlayerWidget.h"
#include "ui_DarkBluePlayerWidget.h"
#include <QFile>
#include <pluginmanager.h>
#include <QResizeEvent>
#include <QDebug>
#include <QPainter>
#include <QSharedPointer>
#include "icore.h"
#include "iplaybackcontroller.h"
#include "iplaylist.h"
#include "CoreData/song.h"
#include "CoreSupply/AssetController.h"
#include "math.h"
#include "Settings/SettingsManager.h"


DarkBluePlayerWidget::DarkBluePlayerWidget(QWidget *parent) :
    IPlayerWidget(parent),
    ui(new Ui::DarkBluePlayerWidget),
    window(0),
    playerControl(0)
{
    ui->setupUi(this);
    loadStylesheet();

    bool showNextDisplay;

    Core::SettingsModule *playerSettings = Core::ICore::settingsManager()->getModule("org.safri.darkblueplayer");

    if (playerSettings)
    {
        showNextDisplay = playerSettings->getSetting("showNextSongDisplay").toBool();
    }
    else
    {
        showNextDisplay = false;
    }

    if (!showNextDisplay)
    {
        ui->nextSongCover->setVisible(false);
        ui->nextSongInfo->setVisible(false);
    }

    changePlaybackController();

//    QMainWindow* window = qApp->findChildren<QMainWindow *>().at(0);
/*

*/
     connect(PluginSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)), this, SLOT(objectAddedToObjectPool(QObject*)));
     qDebug()<<"HAAALLLOO";
     setNextSongCover( getCoverPath(0) );

     connect (ui->shuffleButton, SIGNAL(toggled(bool)), this, SLOT(shuffleToggled(bool)));

}

DarkBluePlayerWidget::~DarkBluePlayerWidget()
{
    delete ui;
}

IPlayerWidget::PlayerWidgetPosition DarkBluePlayerWidget::getPreferedPosition()
{
    return IPlayerWidget::BOTTOM;
}

void DarkBluePlayerWidget::loadStylesheet()
{
    QFile file;

    file.setFileName(":stylesheet/DarkBluePlayerStylesheet.css");
    file.open(QFile::ReadOnly);

    QString styleSheet = QLatin1String( file.readAll() );
    file.close();

    this->setStyleSheet(styleSheet);
}

QString DarkBluePlayerWidget::getTimeStringFromMS(int ms)
{
    float tmp = ms / 1000;
    int min = tmp / 60;

    QString minStr = QString::number(min);
    if (min < 10)
    {
        minStr = "0" + minStr;
    }

    int sec = round( ( (int) tmp ) % 60);

    QString secStr = QString::number(sec);
    if (sec < 10)
    {
        secStr = "0" + secStr;
    }

    return minStr + ":" + secStr;
}

QString DarkBluePlayerWidget::getCoverPath(Core::DataItem *dataItem)
{
    QString coverPath;

    coverPath = Core::ICore::instance()->assetController()->getAsset("CoverURL", dataItem ).toString();

    if ( coverPath.isEmpty() )
    {
        coverPath = ":/border_images/Ressources/no_cover.png";
    }

    return coverPath;
}

void DarkBluePlayerWidget::setNextSongCover(QString coverPath)
{
    QPixmap cover = QPixmap( coverPath ).scaled(31, 31, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap result( cover.size() );

    result.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&result);
    painter.setOpacity(0.3);
    painter.drawPixmap(0, 0, cover);
    painter.end();

    ui->nextSongCover->setPixmap( result );
}

void DarkBluePlayerWidget::objectAddedToObjectPool(QObject * object)
{
    QMainWindow* mainWindow = qobject_cast<QMainWindow*>(object);
    if(mainWindow)
    {
      window = mainWindow->centralWidget();
      playerControl = new PlayerControl(window);
      connect(playerControl, SIGNAL( playToggled(bool) ),     this,                                   SLOT( playToggled(bool) ) );
      connect(playerControl, SIGNAL( nextClicked() ),         playbackController->nextAction(),       SLOT( trigger() ) );
      connect(playerControl, SIGNAL( previousClicked() ),     playbackController->previousAction(),   SLOT( trigger() ) );
      window->installEventFilter(this);
      playerControl->move(window->width()/2-74, window->height()-93);
      playerControl->show();
    }
}

void DarkBluePlayerWidget::playToggled(bool isPlaying)
{
    if ( isPlaying )
    {
        playbackController->playAction()->trigger();
    }
    else
    {
        playbackController->pauseAction()->trigger();
    }
}

void DarkBluePlayerWidget::stateChanged(Core::playState state)
{
    switch (state)
    {
        case Core::PLAY:

            if ( playerControl )
            {
                playerControl->setPlaying(true);
            }
            break;

        case Core::STOP:

            if ( playerControl )
            {
                playerControl->setPlaying(false);
            }
            break;

        case Core::PAUSE:

            if ( playerControl )
            {
                playerControl->setPlaying(false);
            }
            break;

        default:
            break;
    }
}

void DarkBluePlayerWidget::update(int currentTime)
{
    int totalTime = playbackController->getMediaTotalTime();

    ui->seekSlider->setMaximum(totalTime);
    ui->seekSlider->setValue(currentTime);

    ui->totalTime->setText( getTimeStringFromMS(totalTime) );
    ui->currentTime->setText( getTimeStringFromMS(currentTime) );
}

void DarkBluePlayerWidget::changePlaybackController()
{
    playbackController = Core::ICore::playbackController();

    connect(playbackController, SIGNAL( mediaChanged(Core::Media*) ),   this, SLOT( mediaChanged(Core::Media*) ) );
    connect(playbackController, SIGNAL( stateChanged(Core::playState)), this, SLOT( stateChanged(Core::playState) ) );
    connect(playbackController, SIGNAL( update(int)),                   this, SLOT( update(int) ) );

    connect(ui->seekSlider,     SIGNAL( sliderMoved(int)),              playbackController,     SLOT( seek(int) ) );
    connect(ui->volumeSlider,   SIGNAL( sliderMoved(int)),              playbackController,     SLOT( setVolume(int) ) );
    connect(playbackController, SIGNAL(volumeChanged(int)),             this->ui->volumeSlider, SLOT(setValue(int)));
}

void DarkBluePlayerWidget::shuffleToggled(bool value)
{
    playbackController->getPlaylist()->setShuffle(value);
}

void DarkBluePlayerWidget::mediaChanged(Core::Media* media)
{
    if ( media->getType() == Core::Media::SONG)
    {
        Core::Song* song = qobject_cast<Core::Song*>(media);
        QString coverPath;

        if(song)
        {
            ui->currentSongInfo->setText( "<b>" + song->getAlbum()->getName() + "</b><br>" + song->getArtist()->getName() + " - " + song->getName() );
            coverPath = getCoverPath( song->getAlbum() );

            ui->coverImage->setPixmap( QPixmap( coverPath ).scaled(63, 63, Qt::IgnoreAspectRatio, Qt::SmoothTransformation) );
        }

        ui->totalTime->setText( getTimeStringFromMS( playbackController->getMediaTotalTime() ) );

        QSharedPointer<Core::IPlaylist> playlist = playbackController->getPlaylist();
        int nextSongPosition = playlist->getCurrentMediaPosition() + 1;

        coverPath = getCoverPath(0);

        if ( nextSongPosition < playlist->getSize() )
        {
            song = qobject_cast<Core::Song*>( playlist->getMediaAt(nextSongPosition) );

            if (song)
            {
                coverPath = getCoverPath( song->getAlbum() );
                ui->nextSongInfo->setText( "<b>Next Song</b><br>" + song->getArtist()->getName() + " - " + song->getName() );
            }

        }
        else
        {            
            ui->nextSongInfo->setText("<b>Next Song</b>");
        }

        setNextSongCover( coverPath );
    }
}

bool DarkBluePlayerWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
            playerControl->move(window->width()/2-74, window->height()-88);
    }
    return false;
}
void DarkBluePlayerWidget::setVolumeEnabled(bool value)
{
    Q_UNUSED(value)
}

void DarkBluePlayerWidget::setSeekerEnabled(bool value)
{
    Q_UNUSED(value)
}
