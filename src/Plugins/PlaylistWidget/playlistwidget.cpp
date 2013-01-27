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

void PlaylistWidget::showPlaylist(Core::IPlaylist *playlist)
{
    QAbstractItemModel* model = ui->playlistView->model();
    delete model;

    playlistModel = new PlaylistModel(playlist, this);
    connect(playlistModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this->ui->playlistView, SLOT(dataChanged(QModelIndex,QModelIndex)));


    ui->playlistView->setModel(playlistModel);
}


void PlaylistWidget::itemsSelected(QList<Core::Item *> selection)
{
}


Core::IPlaylist *PlaylistWidget::newPlaylist()
{
    return 0;
}


void PlaylistWidget::showCurrentPlaylist()
{
}

void PlaylistWidget::on_playlistView_doubleClicked(const QModelIndex &index)
{
    Core::IPlaylist* playlist = playlistModel->getPlaylist();
    playlist->setCurrentMedia(index.row());

    Core::IPlaybackController* playbackConntroller = Core::ICore::playbackController();

    playbackConntroller->stopAction()->trigger();
    playbackConntroller->setPlaylist(playlist);
    playbackConntroller->playAction()->trigger();
}
