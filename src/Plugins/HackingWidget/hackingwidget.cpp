#include "hackingwidget.h"
#include "ui_hackingwidget.h"
#include "icore.h"
#include "Interfaces/IAudioBackend.h"
#include "iplaybackcontroller.h"
#include <QToolBar>
#include "CoreData/song.h"
#include <QList>
#include "iplaylist.h"
#include "CoreData/dataitemtablemodel.h"
#include "pluginmanager.h"
#include "Interfaces/IStorageAdapter.h"
#include <QDebug>

HackingWidget::HackingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HackingWidget)
{
    ui->setupUi(this);
}

HackingWidget::~HackingWidget()
{
    delete ui;
}

void HackingWidget::on_pushButton_clicked()
{
    Core::ICore::audioBackend()->setVolume( ui->lineEdit->text().toInt() );
}

void HackingWidget::on_pushButton_4_clicked()
{
    playbackController = Core::ICore::playbackController();

    QToolBar *bar = new QToolBar(this);

    bar->addAction(playbackController->previousAction());
    bar->addAction(playbackController->playPauseAction());
    bar->addAction(playbackController->stopAction());
    bar->addAction(playbackController->nextAction());
    bar->addAction(playbackController->playAction());
    bar->addAction(playbackController->pauseAction());

    ui->widget->layout()->addWidget(bar);


    Core::Song *testMp31 = new Core::Song(1, "Test", 2012, "x:/audacity-test-file.mp3", this);
    Core::Song *testMp32 = new Core::Song(2, "Test", 2012, "C:\\YellowLedbetter.mp3", this);

    QList<Core::Item*> songs;
    songs.append(testMp31);
    songs.append(testMp32);

    Core::IPlaylist *playList = Core::ICore::createPlaylist();

    playList->insertMediaAt(0, songs);

    playbackController->setPlaylist(playList);
    connect(playbackController, SIGNAL(update(int)), this, SLOT(update(int)));

    Core::DataItemTableModel* model = new Core::DataItemTableModel(5000, 10, this);
    ui->tableView->setModel(model);

    model->setData(model->index(0, 0), "wusel dusel");

}

void HackingWidget::on_verticalSlider_sliderMoved(int position)
{
    Core::ICore::playbackController()->setVolume(position);
}

void HackingWidget::update(int currentTime)
{

    currentTime /= 1000;

    ui->label->setText( QString::number(currentTime) );
}

void HackingWidget::on_pushButton_5_clicked()
{
    int sec = ui->lineEdit_3->text().toInt();
    Core::ICore::playbackController()->seek(sec * 1000);
}

void HackingWidget::on_pushButton_6_clicked()
{
    Core::IStorageAdapter *storageAdapter;
    QList<Core::IStorageAdapter*> objects = PluginSystem::PluginManager::instance()->getObjects<Core::IStorageAdapter>();

    if (objects.size() > 0)
    {
        storageAdapter = objects.at(0);
        qDebug() << storageAdapter->getStorageType();
        ui->tableView->setModel(storageAdapter->loadTableForDataItemType(Core::DataItem::SONG));
    }
}
