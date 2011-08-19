#include "playerwidget.h"
#include "ui_playerwidget.h"
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDrag>
#include <QDragMoveEvent>
#include <QUrl>
#include <QDir>
#include <QDirIterator>
#include <audiofile.h>
#include <playlist.h>
#include <QFileInfo>
#include <QStringList>

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::PlayerWidget), playlist(0)

{

    shortcut_next = new QxtGlobalShortcut(QKeySequence("Media Next"));
    shortcut_play = new QxtGlobalShortcut(QKeySequence("Media Play"));
    shortcut_previous = new QxtGlobalShortcut(QKeySequence("Media Previous"));

    shortcut_next->setEnabled(true);
    shortcut_play->setEnabled(true);
    shortcut_previous->setEnabled(true);

    ui->setupUi(this);
    this->setStyleSheet("background-image:url();");

    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    Phonon::createPath(mediaObject, audioOutput);
    mediaObject->setTickInterval(1000);
    ui->seekSlider->setMediaObject(mediaObject);
    ui->volumeSlider->setAudioOutput(audioOutput);
    machine = new QStateMachine();
    play  = new QState();
    pause = new QState();
    stop  = new QState();
    noData = new QState();
    setupActions();

    play  ->addTransition(playAction, SIGNAL(triggered()), pause);
    pause ->addTransition(playAction, SIGNAL(triggered()), play);
    pause ->addTransition(stopAction, SIGNAL(triggered()), stop);
    play  ->addTransition(stopAction, SIGNAL(triggered()), stop);
    stop  ->addTransition(playAction, SIGNAL(triggered()), play);
    pause ->addTransition(nextAction, SIGNAL(triggered()),play);
    pause ->addTransition(previousAction, SIGNAL(triggered()),play);
    stop  ->addTransition(nextAction, SIGNAL(triggered()), play);
    stop  ->addTransition(previousAction, SIGNAL(triggered()), play);
    noData->addTransition(playAction, SIGNAL(triggered()), play);


    machine->addState(play);
    machine->addState(pause);
    machine->addState(stop);
    machine->addState(noData);
    machine->setInitialState(noData);
    machine->start();

    //connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    bar = new QToolBar(this);


    ui->horizontalLayout_2->addWidget(bar);




    bar->addAction(previousAction);
    bar->addAction(playAction);
    bar->addAction(stopAction);
    bar->addAction(nextAction);
    bar->addAction(shuffleAction);

    connect(play, SIGNAL(entered()), this, SLOT(playStateSlot()));
    connect(pause, SIGNAL(entered()), this, SLOT(pauseStateSlot()));
    connect(stop, SIGNAL(entered()), this, SLOT(stopStateSlot()));
    connect(mediaObject, SIGNAL(finished()), this, SLOT(currentSongFinished()));
    connect(nextAction,SIGNAL(triggered()) ,this, SLOT(nextActionSlot()));
    connect(previousAction,SIGNAL(triggered()) ,this, SLOT(previousActionSlot()));

    connect (noData, SIGNAL(entered()), this, SLOT(noDataSlot()));
    connect(shuffleAction, SIGNAL(triggered(bool)), this, SLOT(shuffleActionSlot(bool)));

    ui->info->setMargin(2);
    ui->info->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    ui->info->setLineWidth(2);
    ui->info->setAutoFillBackground(true);

    QPalette palette;
    palette.setBrush(QPalette::WindowText, Qt::white);

    ui->info->setStyleSheet("border-image:url(img/display.png) ; border-width:3px");
    ui->info->setPalette(palette);
    ui->info->setText(tr("<center>No media</center>"));

    connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)), this, SLOT(currentSourceChanged(Phonon::MediaSource)));
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(updateInfo()));


    connect(this->shortcut_next, SIGNAL(activated()), this, SLOT(nextActionSlot()));
    connect(this->shortcut_play, SIGNAL(activated()), this->playAction, SLOT(trigger()));
    connect(this->shortcut_previous, SIGNAL(activated()), this, SLOT(previousActionSlot()));
    //connect(this->shortcut_pause, SIGNAL(activated()), this, SLOT(pauseStateSlot()));


    mediaObject->setTickInterval(10);
this->setAcceptDrops(true);
  }

PlayerWidget::~PlayerWidget()
{
    delete ui;
}



void PlayerWidget::setPlaylist(Playlist* value)
{
    this->playlist = value;
    if(shuffleAction->isChecked()) value->setShuffle(true);
}

void PlayerWidget::playSongAt(int value)
{

    if (!stopped) stopAction->trigger();

    playlist->setCurrentPlayingSong(value);
    AudioFile* af = playlist->getAudioFileAt(value);

    af->ReadTags();

    mediaObject->setCurrentSource(*playlist->getAudioFileAt(value));
    playAction->trigger();


}

void PlayerWidget::mouseDoubleClickEvent(QMouseEvent * event)
{

    Q_EMIT viewModeChanged();

}




void PlayerWidget::setupActions()
{

    shuffleAction = new QAction(QIcon("img/shuffle_icon.png"), tr("Shuffle"), this);
    shuffleAction->setCheckable(true);
    shuffleAction->setChecked(false);


    playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    playAction->setShortcut(tr("Ctrl+P"));
    playAction->setDisabled(false);

    stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    stopAction->setShortcut(tr("Ctrl+S"));
    stopAction->setDisabled(false);
    nextAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipForward), tr("Next"), this);
    nextAction->setShortcut(tr("Ctrl+N"));
    previousAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipBackward), tr("Previous"), this);
    previousAction->setShortcut(tr("Ctrl+R"));
}






void PlayerWidget::playStateSlot()
{
    shuffleAction->setDisabled(false);
    nextAction->setDisabled(false);
    previousAction->setDisabled(false);
    playAction->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    stopped = false;
   stopAction->setDisabled(false);
   playAction->setDisabled(false);
   mediaObject->play();
}

void PlayerWidget::pauseStateSlot()
{
    mediaObject->pause();
    playAction->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    stopped = false;
}

void PlayerWidget::stopStateSlot()
{

    stopAction->setDisabled(true);
    stopped = true;
    playAction->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    mediaObject->stop();
}

void PlayerWidget::currentSongFinished()
{
     if (!stopped)
     {
        AudioFile *nextSong = playlist->getNextSong();
        nextSong->ReadTags();
        if (nextSong != currentSong)
        {
            mediaObject->setCurrentSource(*nextSong);
            mediaObject->play();
        }
        else
        {
            stopAction->trigger();
        }
     }

}
void PlayerWidget::nextActionSlot()
{
    stopAction->trigger();

    AudioFile *nextSong = playlist->getNextSong();
    nextSong->ReadTags();

    if (nextSong != 0)
    {
        mediaObject->setCurrentSource(*nextSong);
        playAction->trigger();
    }

}


void PlayerWidget::previousActionSlot()
{
    stopAction->trigger();
    mediaObject->setCurrentSource(*playlist->getPreviousSong());

    playAction->trigger();


}

void PlayerWidget::shuffleActionSlot(bool value)
{

    if (playlist) playlist->setShuffle(value);

}



void PlayerWidget::noDataSlot()
{
    shuffleAction->setDisabled(true);
    stopAction->setDisabled(true);
    nextAction->setDisabled(true);
    previousAction->setDisabled(true);
    playAction->setDisabled(true);

}



Playlist *PlayerWidget::getPlaylist()
{
    return playlist;
}

void PlayerWidget::updateInfo()
{
    long len = mediaObject->totalTime();
    long pos = mediaObject->currentTime();
    QString timeString;
    if (pos || len)
    {
        int sec = pos/1000;
        int min = sec/60;
        int hour = min/60;
        int msec = pos;

        QTime playTime(hour%60, min%60, sec%60, msec%1000);
        sec = len / 1000;
        min = sec / 60;
        hour = min / 60;
        msec = len;

        QTime stopTime(hour%60, min%60, sec%60, msec%1000);
        QString timeFormat = "m:ss";
        if (hour > 0)
            timeFormat = "h:mm:ss";
        timeString = playTime.toString(timeFormat);
        if (len)
            timeString += " / " + stopTime.toString(timeFormat);
    }

    if (currentSong != 0)
    {
        ui->info->setText("<center> .: " + currentSong->getArtist() + " - " + currentSong->getTitle() + " :.<br>("+ timeString + ")</center>");
    }

    mediaObject->setTickInterval(200);
}

void PlayerWidget::currentSourceChanged(Phonon::MediaSource source)
{
    this->currentSong = playlist->getCurrentPlayingAudioFile();

    mediaObject->setTickInterval(10);

    Q_EMIT currentSourceChanged(this->currentSong);

    updateInfo();
}




void PlayerWidget::dragEnterEvent(QDragEnterEvent *event)
 {
    bool accepted = true;
    const QMimeData *mimeData = event->mimeData();
event->acceptProposedAction();
    if (mimeData->hasUrls())
    {

        QList<QUrl> urllist = mimeData->urls();
        foreach (QUrl i, urllist)
        {


        }

    }

 }



void PlayerWidget::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {

        QList<QUrl> urllist = mimeData->urls();
        QList<AudioFile*>* songlist = new QList<AudioFile*>;


        foreach (QUrl i, urllist)
        {

            if (getSupportedFileTypes()->contains("*."+QFileInfo(i.toLocalFile()).suffix().toLower()))
            {
                AudioFile* song = new AudioFile(i.toLocalFile());
                songlist->append(song);

            }

            else
            {


                if (!i.isEmpty())
                {

                    QDir dir(i.toLocalFile());
                    QStringList* filters = getSupportedFileTypes();

                    dir.setNameFilters(*filters);

                    QDirIterator lukeFileWalker(dir, QDirIterator::Subdirectories);


                    while (lukeFileWalker.hasNext())
                    {
                        lukeFileWalker.next();
                        AudioFile* af = new AudioFile(lukeFileWalker.fileInfo().absoluteFilePath());
                        songlist->append(af);
                    }


                }
            }

        }

        if (songlist->size()>0)
        {
            if (playlist) this->playlist->setCurrentPlayingSong(-1);
              Playlist* pl = new Playlist(songlist);

              this->setPlaylist(pl);
              this->playSongAt(0);

        }



    }
}


QStringList* PlayerWidget::getSupportedFileTypes()
{
    QStringList* values = new QStringList();
    QStringList list = Phonon::BackendCapabilities::availableMimeTypes();
    for (int i = 0; i < list.size();i++)
    {
        QString value = list.at(i);

        if (
            value.startsWith("audio/mp3")||value.startsWith("audio/flac")
            ||value.startsWith("audio/ogg")||value.startsWith("audio/m4a")
            ||value.startsWith("audio/wma")
            )
        {

            values->append("*."+value.section("/",1));
        }


    }
   if(list.contains("audio/mp4"))
    values->append("*.m4a");
   return values;

}

