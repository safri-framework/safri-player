#include "playlistwidget.h"
#include "ui_playlistwidget.h"
#include "playlistmodel.h"
#include <QDebug>
#include "../CorePlugin/iplaybackcontroller.h"
#include "../CorePlugin/icore.h"

PlaylistWidget::PlaylistWidget(QWidget *parent) :
    IPlaylistWidget(parent),
    ui(new Ui::PlaylistWidget)
{
    ui->setupUi(this);
}

PlaylistWidget::~PlaylistWidget()
{
    delete ui;
}

void PlaylistWidget::showPlaylist(QSharedPointer<Core::IPlaylist> playlist)
{
    QAbstractItemModel* model = ui->playlistView->model();

    delete model;

    playlistModel = new PlaylistModel(playlist, this);
    connect(playlistModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this->ui->playlistView, SLOT(dataChanged(QModelIndex,QModelIndex)));


    ui->playlistView->setModel(playlistModel);
}


void PlaylistWidget::itemsSelected(QList<Core::Item *> selection)
{
    Q_UNUSED(selection)
}


QSharedPointer<Core::IPlaylist> PlaylistWidget::newPlaylist()
{
    return QSharedPointer<Core::IPlaylist>();
}


void PlaylistWidget::showCurrentPlaylist()
{
}

void PlaylistWidget::on_playlistView_doubleClicked(const QModelIndex &index)
{
    QSharedPointer<Core::IPlaylist> playlist = playlistModel->getPlaylist();
    playlist->setCurrentMedia(index.row());

    Core::IPlaybackController* playbackConntroller = Core::ICore::playbackController();

    playbackConntroller->stopAction()->trigger();
    playbackConntroller->setPlaylist(playlist);
    playbackConntroller->playAction()->trigger();
}

void PlaylistWidget::on_pushButton_clicked()
{
    QAbstractItemModel* model = ui->playlistView->model();

     //TODO: Check if old Playlist will be deleted.


    delete model;

    QSharedPointer<Core::IPlaylist> pl = Core::ICore::createPlaylist();
    playlistModel = new PlaylistModel(pl, this);
    connect(playlistModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this->ui->playlistView, SLOT(dataChanged(QModelIndex,QModelIndex)));


    ui->playlistView->setModel(playlistModel);
}
