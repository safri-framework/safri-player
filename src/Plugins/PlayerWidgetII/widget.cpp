#include "widget.h"
#include "ui_widget.h"
#include "QFile"
#include "Interfaces/ICore.h"
#include <QDebug>
#include <QIcon>
#include <QMovie>

#include "../CorePlugin/CoreData/Song.h"

Widget::Widget(QWidget *parent) :
    IPlayerWidget(parent),
    m_pbController(Core::ICore::playbackController()),
    ui(new Ui::Widget),
    loaderGif(0)
{
    firstPlayback = false;
    ui->setupUi(this);
    this->ui->infoLabel->setMinimumWidth(0);
    this->ui->infoLabel->setMaximumWidth(0);
    QFile file;
    file.setFileName(":/style/styles.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);

    connect(this->ui->next, SIGNAL(clicked()), m_pbController->nextAction(), SLOT(trigger()));
    connect(this->ui->play, SIGNAL(clicked()), m_pbController->playPauseAction(), SLOT(trigger()));
    connect(this->ui->previous, SIGNAL(clicked()), m_pbController->previousAction(), SLOT(trigger()));

    //connect(m_pbController->nextAction(), SIGNAL(changed()), this, SLOT(actionChanged()));
    //connect(m_pbController->previousAction(), SIGNAL(changed()), this, SLOT(actionChanged()));
    //connect(m_pbController->playPauseAction(), SIGNAL(changed()), this, SLOT(actionChanged()));

    connect(m_pbController, SIGNAL(stateChanged(Core::playState)), this, SLOT(stateChanged(Core::playState)));
    connect(m_pbController, SIGNAL(mediaChanged(Core::Media*)), this, SLOT(mediaChanged(Core::Media*)));
    connect(m_pbController, SIGNAL(volumeChanged(int)), this, SLOT(volumeChanged(int)));
    connect(m_pbController, SIGNAL(update(int)), this, SLOT(update(int)));
    connect(m_pbController->shuffleAction(), SIGNAL(toggled(bool)), this, SLOT(shuffleActionChecked(bool)));
    qDebug()<<"Current Volume"<<m_pbController->getVolume();
    ui->volume_slider->setValue(100);
    //this->showLoadingIndicator("HALLO (=");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setSeekerEnabled(bool value)
{
   // this->ui->seek_slider->setEnabled(value);
    this->ui->seek_slider->setVisible(value);
}

void Widget::setVolumeEnabled(bool value)
{
    this->ui->volume_slider->setEnabled(value);
}

void Widget::showLoadingIndicator(QString msg)
{
    Q_UNUSED( msg )
    this->ui->time_label->hide();
    this->ui->loaderLabel->show();
    if(!loaderGif)
        loaderGif = new QMovie(":/other/SAFRI_UI/loader.gif");
    this->ui->loaderLabel->setMovie(loaderGif);
    loaderGif->start();

}

void Widget::hideLoadingIndicator()
{
    this->ui->time_label->show();
    this->ui->loaderLabel->hide();
    if(loaderGif)
    {
        delete loaderGif;
        loaderGif = 0;
    }
}


IPlayerWidget::PlayerWidgetPosition  Widget::getPreferedPosition()
{
    return IPlayerWidget::BOTTOM;
}

void Widget::mediaChanged(Core::Media *media)
{
    newMedia = true;
    if(!firstPlayback)
    {
        this->ui->infoLabel->setMaximumWidth(350);
        firstPlayback = true;
    }
    int totalTime = m_pbController->getMediaTotalTime();
    ui->seek_slider->setMaximum(totalTime);
    ui->seek_slider->setValue(0);
    if ( media->getType() == Core::Media::SONG)
    {
        Core::Song* song = qobject_cast<Core::Song*>(media);
        if(song)
        ui->infoLabel->setText(song->getArtist()->getName() + "\n" + song->getName());
    }
    else
    {
        ui->infoLabel->setText(media->getName());
    }
}


void Widget::update(int currentTime)
{
    if(newMedia)
    {

        newMedia = false;
    }

    int totalTime = m_pbController->getMediaTotalTime();
    ui->seek_slider->setMaximum(totalTime);

    ui->seek_slider->setValue(currentTime);

    int tmp = currentTime/1000;
    int h = tmp / 3600;
    tmp = tmp % 3600;
    int min = tmp / 60;
    int sec = tmp % 60;

    QString minStr = QString::number(min);
    /*
    if (min <10)
    {
        minStr = "0"+minStr;
    }
*/


    QString secStr = QString::number(sec);
    if (sec <10)
    {
        secStr = "0"+secStr;
    }



    if(h == 0)
    {
        this->ui->time_label->setText(minStr+":"+secStr);
    }
    else
    {
        this->ui->time_label->setText(QString::number(h)+":"+minStr+":"+secStr);
    }
}

void Widget::actionChanged()
{
    ui->play->setEnabled(m_pbController->playPauseAction()->isEnabled());
    ui->next->setEnabled(m_pbController->playPauseAction()->isEnabled());
    ui->previous->setEnabled(m_pbController->playPauseAction()->isEnabled());


    //ui->play->setIcon(m_pbController->playPauseAction()->icon());
}

void Widget::stateChanged(playState state)
{
    //qDebug()<<"STATE"<<state;
    if(state != NODATA)
    {
        this->ui->play->setEnabled(true);
        this->ui->previous->setEnabled(true);
        this->ui->next->setEnabled(true);
    }

    switch(state)
    {
        case NODATA:
        {
            this->ui->play->setEnabled(false);
            this->ui->previous->setEnabled(false);
            this->ui->next->setEnabled(false);
            this->ui->play->setIcon(QIcon(":/icons/SAFRI_UI/play_icon.png"));
            return;
        }

        case PLAY:
        {
        //qDebug()<<"PAUSE_ICON";
            this->ui->play->setIcon(QIcon(":/icons/SAFRI_UI/pause_icon2.png"));
            this->hideLoadingIndicator();
            return;
        }

        case STOP:
        {
        //qDebug()<<"PLAY_ICON";
            this->ui->play->setIcon(QIcon(":/icons/SAFRI_UI/play_icon.png"));
            return;
        }

        case PAUSE:
        {
        //qDebug()<<"PLAY_ICON";
            this->ui->play->setIcon(QIcon(":/icons/SAFRI_UI/play_icon.png"));
            return;
        }

    case BUFFERING:
        qDebug()<<"B U F F E R I N G";
        this->showLoadingIndicator("Buffering");
        return;

    }
}

void Widget::on_seek_slider_sliderMoved(int position)
{
    m_pbController->seek(position);
}


void Widget::on_volume_slider_sliderMoved(int position)
{
    //qDebug() << "PlayerWidgetII: setVolume: " << position;
    m_pbController->setVolume(position);
}

void Widget::on_random_toggled(bool checked)
{
    qDebug()<<"SHUFFLE "<<checked;
    m_pbController->shuffleAction()->setChecked(checked);
    //m_pbController->shuffleAction()->setChecked(checked);
}

void Widget::shuffleActionChecked(bool checked)
{
    if(this->ui->random->isChecked() != checked)
    {
        this->ui->random->setChecked(checked);
    }
}

void Widget::on_repeat_toggled(bool checked)
{
    Q_UNUSED( checked )
}

void Widget::volumeChanged(int volume)
{
    ui->volume_slider->setValue(volume);
}
