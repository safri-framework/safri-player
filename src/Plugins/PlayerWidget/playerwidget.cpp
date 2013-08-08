#include "playerwidget.h"
#include "ui_playerwidget.h"
#include <QToolBar>
#include <QDebug>
#include <QFile>
#include <QPalette>

#include "iplaybackcontroller.h"
#include "icore.h"
#include "CoreData/media.h"

PlayerWidget::PlayerWidget(QWidget *parent) :
    IPlayerWidget(parent), ui(new Ui::PlayerWidget), playbackController(Core::ICore::playbackController())
{
    ui->setupUi(this);

    QFile file;
    file.setFileName(":/style/ressources/stylesheet.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);

    QPalette palette;
    palette.setBrush(QPalette::WindowText, Qt::white);

    ui->info->setStyleSheet("border-image:url(:images/ressources/display.png) ; border-width:3px");
    ui->info->setPalette(palette);
    ui->info->setText(tr("<center>No media</center>"));

    ui->info->setMargin(2);
    ui->info->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    ui->info->setLineWidth(2);
    ui->info->setAutoFillBackground(true);

    QToolBar *toolBar = new QToolBar(this);
    ui->sliderToolbarLayout->addWidget(toolBar);
    toolBar->setProperty("type","playerControls");
    toolBar->setStyleSheet("QToolBar{border:none;}");

    toolBar->addAction(playbackController->previousAction());
    toolBar->addAction(playbackController->playPauseAction());
    toolBar->addAction(playbackController->stopAction());
    toolBar->addAction(playbackController->nextAction());

    connect(playbackController, SIGNAL(mediaChanged(Core::Media*)), this, SLOT(mediaChanged(Core::Media*)));
    connect(playbackController, SIGNAL(update(int)), this, SLOT(update(int)));

    ui->volumeSlider->setValue(100);
    this->setMaximumHeight(100);
    this->setMinimumHeight(100);
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

IPlayerWidget::PlayerWidgetPosition PlayerWidget::getPreferedPosition()
{
    return UNDER_PLAYLIST;
}

void PlayerWidget::setVolumeEnabled(bool value)
{
    this->ui->volumeSlider->setEnabled(value);
}

void PlayerWidget::setSeekerEnabled(bool value)
{
    this->ui->seekSlider->setEnabled(value);
}

void PlayerWidget::on_volumeSlider_sliderMoved(int position)
{
    playbackController->setVolume(position);
}

void PlayerWidget::mediaChanged(Core::Media *media)
{
    Q_UNUSED(media)
    int totalTime = playbackController->getMediaTotalTime();
    ui->seekSlider->setMaximum(totalTime);
    ui->seekSlider->setValue(0);
}

void PlayerWidget::update(int currentTime)
{
    ui->seekSlider->setValue(currentTime);
}

void PlayerWidget::on_seekSlider_sliderMoved(int position)
{
    playbackController->seek(position);
}
