#include "DarkBluePlayerWidget.h"
#include "ui_DarkBluePlayerWidget.h"
#include <QFile>
#include <pluginmanager.h>
#include <QResizeEvent>
#include <QDebug>
#include "icore.h"
#include "iplaybackcontroller.h"
#include "CoreData/song.h"
#include "CoreSupply/AssetController.h"
#include "math.h"

DarkBluePlayerWidget::DarkBluePlayerWidget(QWidget *parent) :
    IPlayerWidget(parent),
    ui(new Ui::DarkBluePlayerWidget),
    window(0),
    playerControl(0)
{
    ui->setupUi(this);
    loadStylesheet();
    changePlaybackController();

//    QMainWindow* window = qApp->findChildren<QMainWindow *>().at(0);
/*

*/
     connect(PluginSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)), this, SLOT(objectAddedToObjectPool(QObject*)));

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

void DarkBluePlayerWidget::objectAddedToObjectPool(QObject * object)
{
    QMainWindow* mainWindow = qobject_cast<QMainWindow*>(object);
    if(mainWindow)
    {
      window = mainWindow->centralWidget();
      playerControl = new PlayerControl(window);
      connect(playerControl, SIGNAL(playToggled(bool)),     this,                               SLOT( playToggled(bool) ) );
      connect(playerControl, SIGNAL(nextClicked()),         playbackController->nextAction(),   SLOT( trigger() ) );
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

void DarkBluePlayerWidget::update(int currentTime)
{
    int totalTime = playbackController->getMediaTotalTime();

    ui->seekSlider->setMaximum(totalTime);
    ui->seekSlider->setValue(currentTime);

    /*
    int tmp = currentTime/1000;
    int h = tmp / 3600;
    tmp = tmp % 3600;
    int min = tmp / 60;
    int sec = tmp % 60;

    QString minStr = QString::number(min);

    QString secStr = QString::number(sec);
    if (sec <10)
    {
        secStr = "0"+secStr;
    }
    */

    float tmp = currentTime / 1000;
    int min = tmp / 60;

    QString minStr = QString::number(min);
    if (min < 10)
    {
        minStr = "0" + minStr;
    }

    int sec = round( ( (int) tmp ) % 60) + 1;

    QString secStr = QString::number(sec);
    if (sec < 10)
    {
        secStr = "0" + secStr;
    }

    this->ui->currentTime->setText(minStr+":"+secStr);


}

void DarkBluePlayerWidget::changePlaybackController()
{
    playbackController = Core::ICore::playbackController();

    connect(playbackController, SIGNAL( mediaChanged(Core::Media*) ),   this, SLOT( mediaChanged(Core::Media*) ) );
    connect(playbackController, SIGNAL( update(int)),                   this, SLOT( update(int) ) );
    connect(ui->seekSlider,     SIGNAL( sliderMoved(int)),              playbackController, SLOT( seek(int) ) );
}

void DarkBluePlayerWidget::mediaChanged(Core::Media* media)
{
    if ( media->getType() == Core::Media::SONG)
    {
        Core::Song* song = qobject_cast<Core::Song*>(media);

        if(song)
        {
            ui->currentSongInfo->setText( "<b>" + song->getAlbum()->getName() + "</b><br>" + song->getArtist()->getName() + " - " + song->getName() );
            QString coverPath = Core::ICore::instance()->assetController()->getAsset("CoverURL", song->getAlbum() ).toString();

            if ( coverPath.isEmpty() )
            {
                coverPath = ":/border_images/Ressources/no_cover.svg";
            }

            ui->coverImage->setPixmap( QPixmap( coverPath ).scaled(63, 63, Qt::IgnoreAspectRatio, Qt::SmoothTransformation) );
        }
    }
}

bool DarkBluePlayerWidget::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::Resize)
    {
            qDebug()<<"TEST";
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
